#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

void setup() {
  // put your setup code here, to run once:
  rf_driver.init();
  Serial.begin(9600);
}

void loop() {
//   put your main code here, to run repeatedly:
    uint8_t buffor[22];
    uint8_t bufforLen = sizeof(buffor);
    // buffor jako tablica, i jego dlugosc, petla oczekiwania na widomosc
    if  ( rf_driver.recv(buffor, &bufforLen))
    {
      Serial.print("Message recived: ");
      Serial.println((char*)buffor);
      
    }
//  Serial.println(analogRead(A0));
//  delay(100);
}
