
void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT_PULLUP);
  Serial.begin(9600);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int odczyt = analogRead(A0);
  int napiecie = odczyt*5/1024;
  Serial.print("\n Odczyt: ");
  Serial.print(napiecie);
  Serial.print("\tWejscie cyfrowe:\t");
  int wejcyf = 0;
  if (digitalRead(8) == LOW) {
    wejcyf = 0;
  } else {
    wejcyf = 1;
  }
  Serial.print(wejcyf);
  delay(1000);
}
