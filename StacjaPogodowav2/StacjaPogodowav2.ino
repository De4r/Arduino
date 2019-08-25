#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <avr/sleep.h>
#include <Adafruit_BMP280.h>
#define DHTPIN 13 // definicja preprocesora
#define DHTTYPE DHT11 // definicja preprocesora

const byte soundInterupt = 2;
const byte pirInterupt = 3;

unsigned long timePrev = 0;
unsigned long timeAct = 0;

float temperatureDht = 0;
float temperatureBmp = 0;
float humidity = 0;
float pressure = 0;
boolean updateFlag = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_BMP280 bmp; // I2C
DHT dht(DHTPIN, DHTTYPE);


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

byte cisnienie[8] = {
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b11111
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
  // put your setup code here, to run once:
  
  
  lcd.begin(); // inicjalizuję lcd
  lcd.print("Czekaj..."); // napis kontrolny

  lcd.createChar(0, termometr);
  lcd.createChar(1, kropla);
  lcd.createChar(2, stopnie);
  lcd.createChar(3, cisnienie);

  if (!bmp.begin(0x76)) {
    lcd.home();
    lcd.print("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_4000); /* Standby time. */
                  
  pinMode(soundInterupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(soundInterupt), stamp, CHANGE);
  pinMode(pirInterupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pirInterupt), stamp, RISING);
  
  dht.begin(); // inicjalizuję czujnik DHT
  delay(3000);
  updateData();
  delay(10000);
  timePrev = millis();
  timeAct = millis();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  timeAct = millis();
  if (updateFlag == true || (timeAct - timePrev > 600000) ){
    lcd.backlight();
    lcd.display();
    lcd.home();
    lcd.clear();
    lcd.print("Dokonuje pomiaru...");
    lcd.blink();
    updateData();
    updateFlag = false;
    delay(5000);
    lcd.noDisplay();
    lcd.noBacklight();
    timePrev = timeAct;
  }
  
  
}

void stamp(){
  updateFlag = true;
}

void updateData() {
  delay(5000);
  temperatureDht = dht.readTemperature();
  humidity = dht.readHumidity();
  delay(1000);
  temperatureBmp = bmp.readTemperature();
  pressure = bmp.readPressure();
  

  
  /*if (isnan(temperatureDht) || isnan(humidity) || isnan(temperatureBmp) || isnan(pressure)) { // sprawdzam czy nie ma błędu odczytu
    lcd.clear();
    lcd.home(); // kursor na 0, 0
    lcd.print("Blad odczytu"); // wypisuję napis na lcd
    return; // wychodzę z pętli
   
  }
  */
  printOutput();
}

void printOutput() {
  lcd.backlight();
  lcd.display();
  lcd.createChar(0, termometr);
  lcd.createChar(1, kropla);
  lcd.createChar(2, stopnie);
  lcd.createChar(3, cisnienie);


  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.print(temperatureDht);
  lcd.write(byte(2));
  lcd.print("C");
  lcd.setCursor(12, 0);
  lcd.print(temperatureBmp);
  lcd.write(byte(2));
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.write((byte)1); // jak ww.
  lcd.print(" ");
  lcd.print(humidity); // wypisuję zmienną wilg
  lcd.print(" %");

  lcd.setCursor(0,2);
  lcd.write(byte(3));
  lcd.print(" ");
  lcd.print(pressure);
  lcd.print(" Pa");
  lcd.print(" ");
  lcd.noBlink();

  
  delay(60000);
  lcd.noDisplay();
  lcd.noBacklight();
}
