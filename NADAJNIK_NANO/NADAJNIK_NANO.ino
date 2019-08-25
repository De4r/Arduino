#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver(2000, 3, 4); // (predkosc, pin odbiorczy, pin nadwczy)

void setup() {
  // put your setup code here, to run once:
  rf_driver.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  const char *msg = "Welcome to the Jungle!!"; 
  // definicja wiadomosci
  rf_driver.send((uint8_t *)msg, strlen(msg)); 
  // wysylanie wiadomosci (rzut(widomosc), dlugosc widomosci)
  rf_driver.waitPacketSent();
  // oczekiwanie na wyslanie wiadomosci
  delay(1000);
  
}
