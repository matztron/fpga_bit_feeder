
/*
 * fpga_bitbang.S
 *
 * Created: 26.11.2022 09:28:52
 *  Author: Matthias Musch
 */ 

 ; Idea:
 ; Get a byte as a argument
 ; Set data line to current index of byte given
 ; Have a rising edge

#include <avr/io.h>             // Defines I/O port aliases
#define __SFR_OFFSET 0          // Use 0 for the I/O register offset

.global send_bytes_via_bitbang
.global init_io_for_bitbang
      
.section .text                  ; Defines a code section

; s_data
; on PORTB
#define s_dataPin 5

; s_clk
; on PORTD
#define s_clkPin 2

; Used to configure the clock and tx pin as output in section 'init_uart'
#define temp r21

; Nicer names for the parameters handed to send_bytes_via_bitbang routine
#define control r24
#define data r22

#define bit_counter r18

; Before sending a byte this section must be run to ensure that the pins are configured correctly
init_io_for_bitbang:
	; Configure pin that transmits bitstream to FPGA
	clr		temp							; clear clk register
	ldi		temp,(1<<s_dataPin)					; load 00100000 into mask register
	out		DDRB, temp						; set PINB5 to output

	; Configure pin that drives FPGA
	clr		temp							; clear clk register
	ldi		temp,(1<<s_clkPin)				; load 00000010 into mask register
	out		DDRD, temp						; set PINB2 to ouput

	; Pull s_data to 0 initially
	cbi		PORTB, s_dataPin
	; Pull s_data to 0 initially
	cbi		PORTD, s_clkPin

  ret

; This section can be called from C:
; The control-bits to send (8bits total) will be stored in R25:R24 
; ...with the actual 8bit data being stored in R24
; The data-bits to send (8bits total) will be stored in R23:R22 
; ...with the actual 8bit data being stored in R22

send_bytes_via_bitbang:

	ldi bit_counter, 8

send_bytes_via_bitbang_loop:

	lsl control							; Shift control bits 1 to left: Carry will now be set if MSB was 1
	
	brcc send_zero_ctrl					; If bit shifted into carry is 1: Send 1, if 0: Send 0
	; send 1
	sbi		PORTB, s_dataPin			; Set s_dataPin to 1
	rjmp	send_data_bit				; Jump over send_zero_ctrl label
	
send_zero_ctrl:
	cbi		PORTB, s_dataPin			; Set s_dataPin to 0

send_data_bit:
	; Have a rising edge for the control
	sbi		PORTD, s_clkPin				; Set s_clkPin to 1

	lsl data							; Shift copy of control bits 1 to left: Carry will now be set if MSB was 1

	brcc send_zero_data
	; send 1
	sbi		PORTB, s_dataPin			; Set s_dataPin to 1
	rjmp	end_iteration				; Jump over send_zero_data label
	
send_zero_data:
	cbi		PORTB, s_dataPin			; Set s_dataPin to 0

end_iteration:
	; Have a falling edge
	cbi		PORTD, s_clkPin				; Set s_clkPin to 0

	dec		bit_counter					; decrement bit_counter
	brne	send_bytes_via_bitbang_loop	; if not 0 continue in loop with next bits to send

	ret ; Return to calling C code
