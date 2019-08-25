#include <RH_ASK.h>
#include <SPI.h>
#include <DHT.h> // dołączam bibliotekę od obsługi czujnika DHTxx (pamiętaj żeby zainstalować dodatkową bibliotekę Adafruit Unified Sensor Library)

#define DHTPIN 2 // definicja preprocesora
#define DHTTYPE DHT11 // definicja preprocesora

RH_ASK rf_driver(2000, 3, 4); // (predkosc, pin odbiorczy, pin nadwczy)
DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;

String strHumidity;
String strTemperature;
String strOut;

void setup() {
  // put your setup code here, to run once:
  rf_driver.init();
  dht.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(3000);
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    strHumidity = String(humidity);
    strTemperature = String(temperature);
    strOut = strHumidity + "," + strTemperature;

    static char *msg = strOut.c_str();

    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(2000);
}
