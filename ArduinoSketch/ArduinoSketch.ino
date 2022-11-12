#include "fpga_uart.h"

void setup() {
  // put your setup code here, to run once:
  init_uart();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t my_data = 0xFA;
  send_byte_via_uart(my_data);
  delay(1000);
}

// Notes
// https://forum.arduino.cc/t/solved-linker-error-undefined-reference-with-code-from-avr-crypto-lib/250122/7
// http://nerdralph.blogspot.com/2013/12/writing-avr-assembler-code-with-arduino.html WITH INTERRUPT DISABLING & ENABLING
// For now interrupts are simply enabled
