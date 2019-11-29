#include <DHT.h> // dołączam bibliotekę od obsługi czujnika DHTxx (pamiętaj żeby zainstalować dodatkową bibliotekę Adafruit Unified Sensor Library)
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>


#define DHTPIN 11 // definicja preprocesora
#define DHTTYPE DHT11 // definicja preprocesora
#define vccPin 8
#define lmPin 0
#define serialStatePin 13
#define serialButtonPin 3
#define lcdStateButtonPin 2

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp; // I2C
LiquidCrystal_I2C lcd(0x27, 20, 4);

float humidDHT, pressureBMP, altitudeBMP;
float tempDHT, tempBMP, tempLM;
unsigned long currentMillis = 0, previousMillis = 0;
const long interval = 1000*60*15;
volatile boolean serialState = true, changes = false;
volatile byte lcdMode=1; // 1 podswietlenie caly czas, 2 podswietlenie przy pomiarze, 3 bez podstwielenia, 4 brak LCD, 5->1

byte thermometr[8] = {
  0b00100,
  0b00110,
  0b00100,
  0b00110,
  0b00100,
  0b01110,
  0b01110,
  0b00000
};

byte blob[8] = {
  0b00100,
  0b00100,
  0b01110,
  0b01110,
  0b10111,
  0b10111,
  0b01110,
  0b00000
};

byte deegreSignMy[8] = {
  0b00010,
  0b00101,
  0b00010,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte pressure[8] = {
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b00100,
  0b00100,
  0b11111
};

void changeSerialState() {
  serialState = !serialState;
  changes = true;

}

void changeLcdMode() {
  lcdMode += 1;
  changes = true;
  previousMillis = 0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(vccPin, OUTPUT);
  digitalWrite(vccPin, HIGH);
  pinMode(serialStatePin, OUTPUT);
  pinMode(serialButtonPin, INPUT_PULLUP);
  interrupts ();
  attachInterrupt(digitalPinToInterrupt(serialButtonPin), changeSerialState, FALLING);
  pinMode(lcdStateButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(lcdStateButtonPin), changeLcdMode, FALLING);
  
  delay(50);
  lcd.begin();
  lcd.createChar(0, thermometr);
  lcd.createChar(1, blob);
  lcd.createChar(2, deegreSignMy);
  lcd.createChar(3, pressure);
  // Turn on the blacklight and print a message.
  lcd.backlight();
  
  dht.begin();
  Serial.begin(9600);
  delay(3000);
  

  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    lcd.print(F("Could not find a valid BMP280 sensor, check wiring!"));
    
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  collectMeasurements();
  lcdDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval || changes == true)
    {
      changes = false;
      collectMeasurements();
      if (serialState == true) {
        SerialPrint();
        digitalWrite(serialStatePin, HIGH);
      } else { digitalWrite(serialStatePin, LOW); }
      lcdDisplay();
      previousMillis = currentMillis;
    }
}

// Definitions

void collectMeasurements() {
  digitalWrite(vccPin, HIGH);
  lcd.setCursor(8,3); lcd.blink();
  delay(2000);
  lcd.noBlink();
  humidDHT = dht.readHumidity();
  tempDHT = dht.readTemperature();

  tempBMP = bmp.readTemperature();
  pressureBMP = bmp.readPressure();
  altitudeBMP = bmp.readAltitude(1014);
  tempLM = analogRead(lmPin);
  tempLM = tempLM * 0.48828125;
  digitalWrite(vccPin, LOW);
}

void SerialPrint() {
  Serial.print(tempBMP, 6);
  Serial.print(",");
  Serial.print(pressureBMP, 6);
  Serial.print(",");
  Serial.print(altitudeBMP, 6);
  Serial.print(",");
  Serial.print(tempDHT, 6);
  Serial.print(",");
  Serial.print(humidDHT, 2);
  Serial.print(",");
  Serial.println(tempLM, 6);
}

void lcdDisplay(){
  switch (lcdMode){
    case 1:
      lcd.backlight();
      lcdContent();
      break;
      
    case 2:
      lcd.backlight();
      lcdContent();
      delay(7000);
      lcd.noBacklight();
      break;
      
    case 3:
      lcd.noBacklight();
      lcdContent();
      break;
      
    case 4:
      lcd.noDisplay();
      lcd.noBacklight();
      break;
      
    case 5:    
      lcdMode=1;
      break;
      
    default: 
      lcdMode=1;
      break;
  }
}

void lcdContent(){
  lcd.display();
  lcd.createChar(0, thermometr);
  lcd.createChar(1, blob);
  lcd.createChar(2, deegreSignMy);
  lcd.createChar(3, pressure);

  lcd.setCursor(0,0);
  lcd.print(" ");
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.write(byte(2));
  lcd.print("C");
  
  lcd.setCursor(9, 0);
  lcd.write((byte)1);
  lcd.setCursor(9, 1);
  lcd.print("%");
  lcd.setCursor(7, 2);
  lcd.print(humidDHT);

  lcd.setCursor(17, 0);
  lcd.write((byte)3);
  lcd.setCursor(16, 1);
  lcd.print("hPa");
  lcd.setCursor(14, 2);
  lcd.print(pressureBMP/100);

  lcd.setCursor(0,1);
  lcd.print(tempBMP);
  lcd.setCursor(0,2);
  lcd.print(tempDHT);
  lcd.setCursor(0,3);
  lcd.print(tempLM);

  lcd.setCursor(9, 3);
  lcd.print("S: ");
  lcd.print(serialState);
  lcd.print("  M: ");
  lcd.print(lcdMode);
}
