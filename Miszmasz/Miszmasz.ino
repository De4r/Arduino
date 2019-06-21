#include <LiquidCrystal_I2C.h>

#define trigPin 12
#define echoPin 11
#define odbi 3
LiquidCrystal_I2C lcd(0x27, 16, 2); // tworzę obiekt klasy LiquidCrystal o nazwie lcd o podanych parametrach


void setup() {
  // put your setup code here, to run once:
  lcd.begin(); // inicjalizuję lcd
  lcd.print("Odleglosc"); // napis kontrolny
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
  pinMode(odbi, INPUT);
  }

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Odleglosc");
  lcd.setCursor(0, 1);
  lcd.print(zmierzOdleglosc());
  lcd.print(" ");
  lcd.print("cm");
  Serial.print(zmierzOdleglosc());
  Serial.print(" cm\n");
  delay(2500);
  lcd.clear();
  lcd.print("Odbiciowy");
  if (digitalRead(odbi) == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Tak");
    Serial.print("Odbiciowy Tak\n");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Nie");
    Serial.print("Odbiciowy NIe\n");
  }
  delay(500);
  lcd.setCursor(0,1);
  int analog = analogRead(A5);
  lcd.print(analog);
  Serial.print(analog);
  Serial.print(" \n");
  delay(2500);
  
}

int zmierzOdleglosc() {
  long czas, dystans;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58;
 
  return dystans;
}
