/*
 * uart.h
 *
 * Created: 05.11.2022 11:22:12
 *  Author: Matthias Musch
 */ 


#ifndef FPGA_UART_H_
#define FPGA_UART_H_

/**
* Initialize the software UART by setting the GPIO pins clock and tx to output
* ...while also disabling interrupts
*
* Implemented in assembly
*
* @param val Value to be output to PORTB
*/

extern "C" {
  void init_uart();
}

//extern void init_uart();

/**
* Send one (1) byte via UART while simultaneously clocking the FPGA
*
* Implemented in assembly
*
* @param data 8bit value to be transmitted via UART
*/

extern "C" {
  void send_byte_via_uart(uint8_t data);
}

//extern void send_byte_via_uart(uint8_t data);



#endif /* FPGA_UART_H_ */
