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

#include "fpga_uart.h"
int main()
{
	init_uart();
		
	while(1) 
	{	
		// Transmit my_data via UART
		uint8_t my_data = 0xAA;
		send_byte_via_uart(my_data);
			
		//Wait for some time
		_delay_ms(1);
	
	}
	  
    return 0;
}