void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  digitalWrite(8, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(7) == LOW) {
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
  } //else { // wersja druga
  //  digitalWrite(8, LOW);
  //}

}
