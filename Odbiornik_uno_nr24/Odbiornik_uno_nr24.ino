// Recieverr Code
#include <SPI.h>
#include "RF24.h"

RF24 radio(9, 10); // Pins on arduino uno : D9 (CE) D10 (SS/ CSN)
const uint64_t pipeName = 0x123456789ABC; // Code for pairing
double dataRecieved; // Data to transmite
double previous=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
    Serial.print("Time from prevoius message: ");
    Serial.println(dataRecieved - previous);
    previous = dataRecieved;
  }
  
}
