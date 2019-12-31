// Reciever Code
/*
 * PINs and connections
 * nRF2401L module with UNO
 *        none -  IRQ 7 8 MISO - D12 (MISO)
 *  D11 (MOSI) - MOSI 5 6 SCK  - D13 (SCK)
 *    D10 (SS) -  SCN 3 4 CE   - D9
 *       3,3V  -  Vcc 1 2 GND  - GND
 */
#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10); // Pins on arduino uno : D9 (CE) D10 (SS/ CSN)
const uint64_t pipeName = 0x123456789ABC; // Code for pairing
double dataRecieved[7]; // Data to recieve
double previous=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(110);
  radio.openReadingPipe(1, pipeName);
  radio.startListening();
  Serial.println("Reciever initialzied!");
}

void loop() {
  // put your main code here, to run repeatedly:
  radio.startListening();
  if (radio.available())
  {
    while (radio.available())
    {
      radio.read(&dataRecieved, sizeof(dataRecieved));
    }
    radio.stopListening();

    for (int i=0; i<7; i++) {
      Serial.print(dataRecieved[i], 8);
      Serial.print(",");
    }
    Serial.println();
  }
  
}
