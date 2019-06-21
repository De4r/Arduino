int odczyt = 0;
int srednia = 0;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while ( count < 11 ) {
    odczyt = odczyt + analogRead(A5);
    count = count + 1;
    delay(100);
  }
  odczyt = odczyt / count;
  count = 0;
  Serial.print("Odczyt: ");
  Serial.print(odczyt, DEC);
  Serial.print(" [DEC]\t");
  Serial.print(odczyt, HEX);
  Serial.print(" [HEX]\t");
  Serial.print(odczyt, OCT);
  Serial.print(" [OCT]\t");
  Serial.print(odczyt, BIN);
  Serial.print(" [BIN]\n");
  odczyt = 0;
  delay(500);
}
