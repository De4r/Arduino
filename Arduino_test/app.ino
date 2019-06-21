#include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd = new LiquidCrystal_I2C()
int ledPin = 13;

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
