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

#ifdef __cplusplus
extern "C" {
  void init_uart();
}
#else
extern void init_uart();
#endif

/**
* Send one (1) byte via UART while simultaneously clocking the FPGA
*
* Implemented in assembly
*
* @param data 8bit value to be transmitted via UART
*/

#ifdef __cplusplus
extern "C" {
  void send_byte_via_uart(uint8_t data);
}
# else
extern void send_byte_via_uart(uint8_t data);
#endif

/**
* Just clock the FPGA with max. frequency possible by GPIO
*
* Implemented in assembly
*
*/
#ifdef __cplusplus
extern "C" {
  void clock_fpga();
}
#else
void clock_fpga();
#endif

#endif /* FPGA_UART_H_ */
