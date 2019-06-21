#include <LiquidCrystal_I2C.h>
#include <DHT.h> // dołączam bibliotekę od obsługi czujnika DHTxx (pamiętaj żeby zainstalować dodatkową bibliotekę Adafruit Unified Sensor Library)

#define DHTPIN 2 // definicja preprocesora
#define DHTTYPE DHT11 // definicja preprocesora

LiquidCrystal_I2C lcd(0x27, 16, 2); // tworzę obiekt klasy LiquidCrystal o nazwie lcd o podanych parametrach

DHT dht(DHTPIN, DHTTYPE); // tworzę obiekt klasy DHT o nazwie dht o podanych parametrach

byte termometr[8] = {
  0b00100,
  0b00110,
  0b00100,
  0b00110,
  0b00100,
  0b01110,
  0b01110,
  0b00000
};

byte kropla[8] = {
  0b00100,
  0b00100,
  0b01110,
  0b01110,
  0b10111,
  0b10111,
  0b01110,
  0b00000
};

byte stopnie[8] = {
  0b00010,
  0b00101,
  0b00010,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};


void setup() {
  lcd.begin(); // inicjalizuję lcd
  lcd.print("Czekaj..."); // napis kontrolny

  lcd.createChar(0, termometr);
  lcd.createChar(1, kropla);
  lcd.createChar(2, stopnie);

  dht.begin(); // inicjalizuję czujnik DHT
}

void loop() {
  delay(2000); // czekam 2s
  float temp = dht.readTemperature(); // tworzę zmienną typu float przechowującą pomiar temperatury
  float wilg = dht.readHumidity(); // tworzę zmienną typu float przechowującą pomiar wilgotności

  if (isnan(temp) || isnan(wilg)) { // sprawdzam czy nie ma błędu odczytu
    lcd.home(); // kursor na 0, 0
    lcd.print("Blad odczytu"); // wypisuję napis na lcd
    return; // wychodzę z pętli
  }

  lcd.home(); // kursor na 0, 0
  lcd.write((byte)0); // rzutuję ikonę termomrtr na typ byte i wyświetlam ją na lcd
  lcd.print(" ");
  lcd.print(temp); // wypisuję zmienną temp
  lcd.print(" ");
  lcd.write((byte)2); // jak ww.
  lcd.print("C");
  lcd.setCursor(0, 1); // kursor na drugi wiersz
  lcd.write((byte)1); // jak ww.
  lcd.print(" ");
  lcd.print(wilg); // wypisuję zmienną wilg
  lcd.print("  %");

}
