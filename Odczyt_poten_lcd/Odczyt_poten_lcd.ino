#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); //Deklaracja typu
  lcd.clear();
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Nap. odczytane");
  lcd.setCursor(0,1);
  lcd.print("0.00V"); 
}

double odczyt = 0;
void loop() {
  // put your main code here, to run repeatedly:
  odczyt = analogRead(A5)*5.0/1024.0;
  lcd.setCursor(0,1);
  lcd.print(odczyt);
  
}
