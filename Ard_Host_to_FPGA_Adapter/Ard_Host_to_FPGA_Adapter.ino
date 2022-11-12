#include "fpga_uart.h"

void blink_led (uint8_t iter) 
{
  for (int i = 0; i < iter; i++) 
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000); 
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);       // initialize UART with baud rate of 9600 bps

  //LED for debugging
  pinMode(LED_BUILTIN, OUTPUT);

  // Setup software UART interface to FPGA
  init_uart();
}



void loop() {
  // put your main code here, to run repeatedly:
  char data_rcvd;
  if(Serial.available() > 0) 
  {
    // READ A BYTE
    data_rcvd = Serial.read();   // read one byte from serial buffer and save to data_rcvd
    

    send_byte_via_uart(data_rcvd);

    // ACKNOWLEDGE BYTE BY SENDING IT BACK
    // ...only in state GET_DATA_STATE
    delay(1);
    Serial.write(data_rcvd);
  }
}
