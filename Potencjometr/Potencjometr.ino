int odczWart = 0;
float napiecie =0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  odczWart = analogRead(A5);
  napiecie = odczWart * (5.0/1024.0);
  Serial.println(napiecie);
  digitalWrite(2,HIGH);
  delay(odczWart);
  digitalWrite(2, LOW);
  delay(odczWart);
}
