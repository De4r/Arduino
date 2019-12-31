// Program odczytuje temperaturę kilku czujników

#include <OneWire.h>
#include <DS18B20.h>

// Numer pinu do którego podłaczasz czujnik
#define ONEWIRE_PIN 10

// Ilość czujników
#define SENSORS_NUM 5

// Adresy czujników
const byte address[SENSORS_NUM][8] PROGMEM = {
  0x28, 0xB1, 0x6D, 0xA1, 0x3, 0x0, 0x0, 0x11,
  0x28, 0x87, 0x6A, 0xA1, 0x3, 0x0, 0x0, 0x1F
};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);

void setup() {
  while(!Serial);
  Serial.begin(9600);

  sensors.begin();
  sensors.request();
}

void loop() {
  if (sensors.available())
  {
    for (byte i=0; i<SENSORS_NUM; i++)
    {
      float temperature = sensors.readTemperature(FA(address[i]));

      Serial.print(F("#"));
      Serial.print(i);
      Serial.print(F(": "));
      Serial.print(temperature);
      Serial.println(F(" 'C"));
    }

    sensors.request();
  }

  // tu umieść resztę twojego programu
  // Będzie działał bez blokowania
}
