#include <LiquidCrystal_I2C.h>

#define trigPin 12
#define echoPin 11
#define odbi 3
#define buzz 9
#define lm A5
LiquidCrystal_I2C lcd(0x27, 16, 2); // tworzę obiekt klasy LiquidCrystal o nazwie lcd o podanych parametrach


void setup() {
  // put your setup code here, to run once:
  lcd.begin(); // inicjalizuję lcd
  lcd.home();
  lcd.print("Odbiciowy");
  lcd.setCursor(0,1);
  lcd.print("Odl [cm] : "); // napis kontrolny
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
  pinMode(odbi, INPUT);
  pinMode(buzz, OUTPUT);
  }

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if (digitalRead(odbi) == LOW) {
    lcd.setCursor(10,0);
    lcd.print(" - Tak");
    Serial.print("Odbiciowy Tak\n");
  } else {
    lcd.setCursor(10,0);
    lcd.print(" - Nie");
    Serial.print("Odbiciowy Nie\n");
  }
  delay(500);
  lcd.setCursor(10,1);
  lcd.print("    ");
  lcd.setCursor(10,1);
  lcd.print(zmierzOdleglosc());
  Serial.print(zmierzOdleglosc());
  Serial.print(" [cm] \n");
  delay(500);
  float temp;
  temp = analogRead(lm);
  temp = temp * 0.48828125;
  Serial.print(temp);
  Serial.print(" C \n");
}

int zmierzOdleglosc() {
  float czas, dystans;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58.2;
  if (dystans <= 10) {
    tone(buzz, 3000, 100);
    delay(200);
  } else if ( dystans <=20 && dystans > 10) {
  tone(buzz, 2000, 100);
  delay(500);
  } else {
    tone(buzz, 1000, 100);
    delay(1000);
  }
  return dystans;
}
