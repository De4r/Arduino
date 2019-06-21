#include <Arduino.h>
#line 1 "d:\\Arduino\\Arduino_test\\app.ino"
#line 1 "d:\\Arduino\\Arduino_test\\app.ino"
#include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd = new LiquidCrystal_I2C()
int ledPin = 13;

#line 6 "d:\\Arduino\\Arduino_test\\app.ino"
void setup();
#line 12 "d:\\Arduino\\Arduino_test\\app.ino"
void loop();
#line 6 "d:\\Arduino\\Arduino_test\\app.ino"
void setup()
{
	pinMode(ledPin, OUTPUT);

}

void loop()
{
	digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}

