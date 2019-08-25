#include <DHT.h> // dołączam bibliotekę od obsługi czujnika DHTxx (pamiętaj żeby zainstalować dodatkową bibliotekę Adafruit Unified Sensor Library)
#include <RH_ASK.h>
#include <SPI.h>

#define DHTPIN 2 // definicja preprocesora
#define DHTTYPE DHT11 // definicja preprocesora
#define LM35 A0 // definicja preprocesora

DHT dht(DHTPIN, DHTTYPE); // obiekt DHT
RH_ASK rf_driver; // (predkosc, pin odbiorczy, pin nadwczy)

float tempLM35;
float humidDHT;
float tempDHT;

String strHumidDHT;
String strTempDHT;
String strTempLM35;
String strOut;

void setup() {
  // put your setup code here, to run once:
  dht.begin();

  rf_driver.init();
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  tempLM35 = analogRead(LM35); //Odczytanie napięcia z czujnika temperatury
  tempLM35 = tempLM35 * 0.48828125; //Wyznaczenie temperatury
  
  humidDHT = dht.readHumidity(); // Odczytanie wilgotnosci 
  tempDHT = dht.readTemperature(); // Odczytnaie temperatury

  strHumidDHT = String(humidDHT);
  strTempDHT = String(tempDHT);
  strTempLM35 = String(tempLM35);

  strOut = strHumidDHT + "," + strTempDHT + "," + strTempLM35;
  

  static char *msg = strOut.c_str();

  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();

  delay(5000);
}
