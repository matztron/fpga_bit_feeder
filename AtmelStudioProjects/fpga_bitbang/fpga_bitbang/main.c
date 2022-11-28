/*
 * fpga_bitbang.c
 *
 * Created: 25.11.2022 21:51:42
 * Author : Matthias Musch
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL //16 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "fpga_bitbang.h"


int main(void)
{
    init_io_for_bitbang();
	
    while (1) 
    {
		// Blink
		/*PORTB |= 0B00100000;
		_delay_ms(1000);
		PORTB &= 0B11011111;
		_delay_ms(1000);*/
		
		uint8_t control[2] = {0xA8, 0xB0};
		uint8_t data[2] = {0xA5, 0x01};
		
		// Send stuff
		send_bytes_via_bitbang(control[0], data[0]);
		//send_bytes_via_bitbang(control[1], data[1]);
		
		_delay_ms(1000);
    }
}

// Fragen:
// Der Strobe: WOhin geht der?