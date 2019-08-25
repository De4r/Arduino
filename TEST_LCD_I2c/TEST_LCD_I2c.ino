#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.print("Start ... ..");
  lcd.blink();
}

void loop() {
  // put your main code here, to run repeatedly:
    lcd.home();
    lcd.clear();
    lcd.print("Elo"); 

    delay(500);
    lcd.home();
    lcd.clear();
    lcd.print("Melo"); 
}
