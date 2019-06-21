# 1 "d:\\Arduino\\Arduino_test\\app.ino"
# 1 "d:\\Arduino\\Arduino_test\\app.ino"
# 2 "d:\\Arduino\\Arduino_test\\app.ino" 2

// LiquidCrystal_I2C lcd = new LiquidCrystal_I2C()
int ledPin = 13;

void setup()
{
 pinMode(ledPin, 0x1);

}

void loop()
{
 digitalWrite(ledPin, 0x1);
    delay(500);
    digitalWrite(ledPin, 0x0);
    delay(500);
}
