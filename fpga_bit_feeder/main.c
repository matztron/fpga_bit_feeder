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
* Initialize the software UART by setting the GPIO pins clock and tx to output
* ...while also disabling interrupts
*
* Implemented in assembly
*
* @param val Value to be output to PORTB
*/
extern void init_uart();
	
/**
* Send one (1) byte via UART while simultaneously clocking the FPGA
*
* Implemented in assembly
*
* @param data 8bit value to be transmitted via UART
*/
extern void send_byte_via_uart(uint8_t data);
	
int main()
{
	init_uart();
		
	while(1) 
	{	
		// Transmit my_data via UART
		uint8_t my_data = 0x12;
		send_byte_via_uart(my_data);
			
		//Wait for some time
		_delay_ms(1);
	
	}
	  
    return 0;
}