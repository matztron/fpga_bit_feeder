#include "fpga_uart.h"
#include "bitstream_data.h"

// See: https://www.arduino.cc/reference/tr/language/variables/utilities/progmem/

#define PUSH_BTN_PIN 3 // On Arduino Nano only Pins2 and 3 are interrupt capable

uint8_t is_programmed = 0;

void reprogram_fpga() {
  // check if fpga has been programmed correctly initially -> Dont program FPGA while it is programmed intially after startup
  if (is_programmed = 1) 
  {
    // disable interrupts
    noInterrupts();

    //reprogram fpga
    program_fpga();

    // enable interrupts
    interrupts();
  }
}

void program_fpga() {
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
}

void setup() {
  // put your setup code here, to run once:

  // debugging
  Serial.begin(9600);
  
  init_uart();

  // Two second delay
  delay(2000);

  // Push Button Pin (gets pulled to ground when pressed)
  pinMode(PUSH_BTN_PIN, INPUT_PULLUP);
  // trigger interrupt on falling edge (button is low when pressed (uses internal pullup) )
  attachInterrupt(digitalPinToInterrupt(PUSH_BTN_PIN), program_fpga, FALLING );

  // load the bitstream stored in FLASH onto Arduino
  program_fpga();

  //Now that the FPGA is initially programmed allow the push button to trigger reconfiguration of the FPGA
  is_programmed = 1;

  

  Serial.println("Done programming now only clock");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Simply clock the FPGA
  clock_fpga(); // this function never returns and runs indefinitly - it might as well be placed in setup-routine :)
  
}
