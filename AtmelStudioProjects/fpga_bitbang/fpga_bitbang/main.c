/*
 * fpga_bitbang.c
 *
 * Created: 25.11.2022 21:51:42
 * Author : Matztron
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB |= 0B00100000; // LED as output
    while (1) 
    {
		PORTB |= 0B00100000;
		_delay_ms(1000);
		PORTB &= 0B11011111;
		_delay_ms(1000);
    }
}

