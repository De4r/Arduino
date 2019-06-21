void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, INPUT_PULLUP);

  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  delay(1000);
  while (digitalRead(5) == HIGH) {}
    
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  delay(1000);
  while (digitalRead(5) == HIGH) {}
  
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  delay(1000);
  while (digitalRead(5) == HIGH) {}
  
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  delay(1000);
  while (digitalRead(5) == HIGH) {}
  
}
