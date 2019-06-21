#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT_PULLUP);
  lcd.begin(16, 2); //Deklaracja typu
  lcd.clear();
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Stoper");
  lcd.setCursor(0,1);
  lcd.print("Wcisnij start!"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  float czas = 0;
  boolean start = false;
  if (digitalRead(8) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Start!");
    delay(500);
    czas = 500.0;
    while (start == false){
      delay(100);
      czas = czas + 100.0;
      lcd.setCursor(0,1);
      lcd.print(czas/1000.0);
      if (digitalRead(8) == LOW) {
        start = true;
      }
    }
    delay(300);
    lcd.setCursor(0, 0);
    lcd.print("Wcisnij przycisk");
    while (digitalRead(8) == HIGH) delay(10);
    start = false;
    setup();
    delay(100);
    
    
  }
  delay(20);
}
