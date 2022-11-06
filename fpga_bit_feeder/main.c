/*
 * fpga_bit_feeder.c
 *
 * Created: 04.11.2022 16:02:08
 * Author : Matthias Musch
 */ 

#ifndef F_CPU
	#define F_CPU 16000000UL //16 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>
	
/**
    * Send value passed to function to PORTB
    *
    * Implemented in assembly
    *
    * @param val Value to be output to PORTB
    */
//extern void send_to_portb_in_asm(uint8_t val);
extern void init_uart();
	
/**
    * Send value passed to function to PORTB
    *
    * Implemented in assembly
    *
    * @param val Value to be output to PORTB
    */
//extern void send_to_portb_in_asm(uint8_t val);
extern void send_uart(uint8_t data);
	
int main()
{
	init_uart();
		
	while(1) 
	{	
		// Transmit my_data via UART
		uint8_t my_data = 0x11;
		send_uart(my_data);
			
		//Wait for some time
		_delay_ms(1);
	
	}
	  
    return 0;
}

// Common questions
// https://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_reg_usage
/* Mixing assembly and C: http://ww1.microchip.com/downloads/en/appnotes/doc42055.pdf
* https://msoe.us/taylor/tutorial/ce2810/candasm */