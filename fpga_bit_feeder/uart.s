
/*
 * uart.s
 *
 * Created: 04.11.2022 17:02:35
 *  Author: Matthias Musch
 */ 

#define __SFR_OFFSET 0          // Use 0 for the I/O register offset
#include <avr/io.h>             // Defines I/O port aliases
#include "uart.h"

.global init_uart
.global send_uart
      
.section .text                  ; Defines a code section

#define clkR r17
#define delay r22
#define bitcounter r23
; parameter 'data' from C function call will be stored here
#define data r24

//#define uart_clk_port PORTB
; Arduino Nano Pin D13 (has built-in LED)
#define txPin 5
; Arduino Nano Pin D10
#define clkPin 2
#define clk_mask r20

#define stop_bits 2

; This section can be called from C:
; The data to send is 8bits and it will be stored in R25:R24 
; ...with the actual 8bit data being stored in R24
init_uart:
	clr		r21								; clear clk register
	ldi		r21,(1<<txPin)					; load 00100000 into mask register
	out		DDRB, r21						; set PINB5 to output
	clr		r21								; clear clk register
	ldi		r21,(1<<clkPin)					; load 00000010 into mask register
	out		DDRD, r21						; set PINB2 to ouput


send_uart:
	clr		clk_mask						; clear clk register
	ldi		clk_mask, (1<<clkPin)			; load 00100000 into mask register

	; SEND BYTE ;
	ldi		bitcounter, 9 + stop_bits		; load reg with num of bits to transmit
											; ...8 data bits + 1 start bit + 1 or 2 stop bits
	com		data							; take the one’s complement of the data to send
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
	ldi		delay, 50

uart_clocking:
	; Toggle the clock pin
	eor		clkR, clk_mask					; toggle clkPin in clk register
	out		PORTD, clkR						; write clk register to port
	dec		delay							; decrement delay
	brne	uart_clocking					; if not 0 continue waiting and toggeling the cloick

	; done waiting
	lsr		data							; LSB (bit0) is loaded into the carry flag
	dec		bitcounter						; bitcounter = bitcounter - 1
	brne	uart_send_next_bit				; If the bitcounter is larger than 0 send next bit	

	sbi		PORTB, txPin					; This is the stop bit?
	ret										; Return to calling C
