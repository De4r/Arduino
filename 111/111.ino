#define diodaniebieska 8
#define diodazolta 9
#define przycisk 10
void setup(){
  Serial.begin(9600); //Ustawienie prędkości transmisji
  Serial.println("Witaj"); //Jednorazowe wysłanie tekstu
  pinMode(diodaniebieska, OUTPUT);
  pinMode(diodazolta, OUTPUT);
  pinMode(przycisk, INPUT_PULLUP);

  digitalWrite(diodaniebieska, LOW);
  digitalWrite(diodazolta, LOW);
  
}
void loop() {
  if (digitalRead (przycisk) == LOW) {
    digitalWrite(diodaniebieska, LOW);
    digitalWrite(diodazolta, HIGH);
    
  } else {
    digitalWrite(diodaniebieska, HIGH);
    digitalWrite(diodazolta, LOW);
    Serial.println("Alarm!");
  }

  while (digitalRead(przycisk) == HIGH) {
    delay(25);
  }
  
}
