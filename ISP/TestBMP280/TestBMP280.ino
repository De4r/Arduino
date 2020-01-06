#include <BH1750.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp1;
Adafruit_BMP280 bmp2;
const int n =0;
// Delay manager to send pings regularly. Because of sleepNode(), this is largely irrelevant.

unsigned long Ts = 2000; // ms
unsigned long interval = Ts - n*200; // ms
unsigned long last_time_sent;

// This sketch is to measure light level with few BMP280 and log them to csv

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  
  //Init the bmps!:
  if (!bmp1.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  
  // Setting bmp280 to forced mode, x1 reading of temp. and pressure, no IIR
  bmp1.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering.  OFF - no continous measurements*/
                  Adafruit_BMP280::STANDBY_MS_4000); /* Standby time. */

  if (!bmp2.begin(0x77)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  
  // Setting bmp280 to forced mode, x1 reading of temp. and pressure, no IIR
  bmp2.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering.  OFF - no continous measurements*/
                  Adafruit_BMP280::STANDBY_MS_4000); /* Standby time. */

}

void loop() {
  // put your main code here, to run repeatedly:
//  if ((millis() - last_time_sent > interval) && (readed == 0)){
//      readed = 1;
//    }
//    
//    if ((millis() - last_time_sent > Ts) && (readed == 1)){
//      printData();
//      readed = 0;
//      last_time_sent = millis();
//    }
    if ((millis() - last_time_sent > interval)){
        Serial.print("1: ");
        Serial.print(bmp1.readTemperature());
        Serial.print(",");
        Serial.print(bmp1.readPressure());

        Serial.print(" 2: ");
        Serial.print(bmp2.readTemperature());
        Serial.print(",");
        Serial.println(bmp2.readPressure());
        last_time_sent = millis();

    }

}
