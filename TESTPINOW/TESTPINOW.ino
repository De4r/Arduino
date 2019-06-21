#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(); // inicjalizuję lcd
  lcd.home();
  lcd.print("dzialam");
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  int wyp = 0;
  digitalWrite(7, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
//  for ( int i=0; i<255; i++) {
//  wyp = wyp +i;
//  analogWrite(11, wyp);
//  analogWrite(10, wyp);
//  analogWrite(9, wyp);
//  analogWrite(6, wyp);
//  analogWrite(5, wyp);
//  analogWrite(3, wyp);
//  }
//  lcd.home();
//  lcd.clear();
//  lcd.print("A4");
//  lcd.setCursor(0,1);
//  lcd.print(analogRead(A4));
//  delay(1000);
//  lcd.home();
//  lcd.clear();
//  lcd.print("A3");
//  lcd.setCursor(0,1);
//  lcd.print(analogRead(A3));
//  delay(1000);
//  lcd.home();
//  lcd.clear();
//  lcd.print("A2");
//  lcd.setCursor(0,1);
//  lcd.print(analogRead(A2));
//  delay(1000);
//  lcd.home();
//  lcd.clear();
//  lcd.print("A1");
//  lcd.setCursor(0,1);
//  lcd.print(analogRead(A1));
//  delay(1000);
//  lcd.home();
//  lcd.clear();
//  lcd.print("A0");
//  lcd.setCursor(0,1);
//  lcd.print(analogRead(A0));
//  delay(1000);
}
