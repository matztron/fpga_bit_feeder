
/*
 * uart.s
 *
 * Created: 04.11.2022 17:02:35
 *  Author: Matthias Musch
 */ 

#include <avr/io.h>             // Defines I/O port aliases
#define __SFR_OFFSET 0          // Use 0 for the I/O register offset

.global init_uart
.global send_byte_via_uart
.global clock_fpga
      
.section .text                  ; Defines a code section

;********************************************************************
; MIGHT BE CHANGED BY USER:
; Number of UART stop bits to be used (either 1 or 2)
#define stop_bits 1
; Prescale factor
#define fpga_clk_division_factor 25
; (addtionally the user might also desire to change the pins of the clock and tx pins)
;********************************************************************

; parameter 'data' from C function call will be stored here
#define data r24

; Arduino Nano Pin D13 (Atmega328p: PB5) (has built-in LED)
; USES PORT B (if a different port is desired the occuraces of DDRB and PORTB in this file have to be changed as well)
#define txPin 5

; Arduino Nano Pin D2 (Atmwega328P: PD2)
; USES PORT D (if a different port is desired the occuraces of DDRD and PORTD in this file have to be changed as well)
#define clkPin 2

; Some nicer names for the registers used in the 'send_byte_via_uart' and 'init_uart' sections :)
#define clkR r17
#define clk_mask r20
#define delay r22
#define bitcounter r23
; Used to configure the clock and tx pin as output in section 'init_uart'
#define temp r21

; Before sending a byte this section must be run to ensure that the pins are configured correctly
init_uart:
	;cli										; Disable interrupts during timed sequence

	; Configure pin that transmits bitstream to FPGA
	clr		temp							; clear clk register
	ldi		temp,(1<<txPin)					; load 00100000 into mask register
	out		DDRB, temp						; set PINB5 to output

	; Configure pin that drives FPGA
	clr		temp							; clear clk register
	ldi		temp,(1<<clkPin)				; load 00000010 into mask register
	out		DDRD, temp						; set PINB2 to ouput

  ret


; This section can be called from C:
; The data to send is 8bits and it will be stored in R25:R24 
; ...with the actual 8bit data being stored in R24
send_byte_via_uart:
	clr		clk_mask						; clear clk register
	ldi		clk_mask, (1<<clkPin)			; load 00100000 into mask register

	; SEND BYTE ;
	ldi		bitcounter, 9 + stop_bits		; load reg with num of bits to transmit
											; ...8 data bits + 1 start bit + 1 or 2 stop bits
	com		data							; take the one�s complement of the data to send
	sec										; set the carry flag
											; ... this results in the START BIT being send

uart_send_next_bit:
	brcc	uart_send_1						; if carry is cleared send a 1 else proceed with sending a 0
	; Send 0
	cbi		PORTB, txPin					; Clear txPin (send 0)
	rjmp	uart_wait						; jump to uart_wait

uart_send_1:
	sbi		PORTB, txPin					; Set txPin (send 1)
	nop										; NOT SURE WHY NECCESSARY TILL NOW... PROBABLY SO IT IS EQUALLY LONG THAN SENDING A 0

uart_wait:
	ldi		delay, (fpga_clk_division_factor * 2) ; 'Times two' because every clock cycle has 1 rising- and 1 falling edge

uart_clocking:
	; Toggle the clock pin
	eor		clkR, clk_mask					; toggle clkPin in clk register
	out		PORTD, clkR						; write clk register to port
	dec		delay							; decrement delay
	brne	uart_clocking					; if not 0 continue waiting and toggeling the cloick

	; Done waiting
	lsr		data							; LSB (bit0) is loaded into the carry flag
	dec		bitcounter						; bitcounter = bitcounter - 1
	brne	uart_send_next_bit				; If the bitcounter is larger than 0 send next bit	

	sbi		PORTB, txPin					; This is the stop bit?
	ret										; Return to calling C code

; After programming use this routine as an endless loop to clock the FPGA
; For now this routine will never return and run forever
clock_fpga:
  ldi    clk_mask, (1<<clkPin)     ; load 00100000 into mask register

  eor clkR, clk_mask    ; toggle PINB0 in led register
  out PORTD, clkR       ; write led register to PORTB
  rjmp  clock_fpga      ; jump back to start

  
