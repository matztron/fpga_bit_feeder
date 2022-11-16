#include "fpga_uart.h"
#include "bitstream_data.h"

// See: https://www.arduino.cc/reference/tr/language/variables/utilities/progmem/

void setup() {
  // put your setup code here, to run once:

  // debugging
  Serial.begin(9600);
  
  init_uart();

  // Two second delay
  delay(2000);

  // Fetch data from FLASH and program on FPGA
  for (int i = 0; i < BITSTREAM1_SIZE; i++) {
    uint8_t data = pgm_read_word_near(bitstream1 + i);

    // debugging
    //Serial.println(data);

    // Program it to FPGA
    send_byte_via_uart(data);

    // to slowly examine sending (purely for debugging...)
    //delay(1000);
  }

  Serial.println("Done programming now only clock");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Simply clock the FPGA
  clock_fpga(); // this function never returns and runs indefinitly - it might as well be placed in setup-routine :)
  
}
