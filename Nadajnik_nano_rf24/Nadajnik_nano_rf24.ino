// Sender Code
#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10); // Pins on arduino nano : D9 (CE) D10 (SS/ CSN)
const uint64_t pipeName = 0x123456789ABC; // Code for pairing
int dataTransmitted; // Data to transmite

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(110);
  radio.openWritingPipe(pipeName);
  
  Serial.println("Sender initialzied!");
}

void loop() {
  // put your main code here, to run repeatedly:
  double actMillis;
  radio.powerUp();
  actMillis = millis();
  Serial.println(actMillis);
  radio.write(&actMillis, sizeof(actMillis));
  radio.powerDown();
  
}
