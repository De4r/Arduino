int odebrane = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potencjometr = analogRead(A5);
  int foto1 = analogRead(A3);
  int foto2 = analogRead(A4);
  while (Serial.available() == 0) delay(100);
  if (Serial.available() > 0 ) {
    odebrane = Serial.read();
  }
  switch (odebrane) {
    case 'd':
    Serial.print("Potencjo: ");
    Serial.print(potencjometr, DEC);
    Serial.print("\tFoto lewy: ");
    Serial.print(foto2, DEC);
    Serial.print("\t Foto prawy: ");
    Serial.print(foto1, DEC);
    break;
    case 'h':
    Serial.print("Potencjo: ");
    Serial.print(potencjometr, HEX);
    Serial.print("\tFoto lewy: ");
    Serial.print(foto2, HEX);
    Serial.print("\t Foto prawy: ");
    Serial.print(foto1, HEX);
    break;
    case 'b':
    Serial.print("Potencjo: ");
    Serial.print(potencjometr, BIN);
    Serial.print("\tFoto lewy: ");
    Serial.print(foto2, BIN);
    Serial.print("\t Foto prawy: ");
    Serial.print(foto1, BIN);
    break;
  }
  delay(100);
  Serial.print("\n Podaj d/h/b");
} 
