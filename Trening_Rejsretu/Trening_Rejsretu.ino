int cPin = 2;
int dPin = 4;
int lPin = 3;
byte data = 0; 
 
void setup() {
  pinMode(lPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  digitalWrite(lPin, LOW);
  shiftOut(dPin, cPin, MSBFIRST, 255);
  digitalWrite(lPin, HIGH);
}
void loop() {
  
  blinkAll(1,500); 
  for (int j = 0; j < 8; j++) {
    lightShiftPinA(j);
    delay(1000);
  }
}
void lightShiftPinA(int p) {
  int pin;
  pin = 1<< p;
  digitalWrite(lPin, LOW);
  shiftOut(dPin, cPin, MSBFIRST, pin);
  digitalWrite(lPin, HIGH);
}
void lightShiftPinB(int p) {
  int pin;
  pin = 1;
 
  for (int x = 0; x < p; x++) {
    pin = pin * 2;
  }
  digitalWrite(lPin, LOW);
  shiftOut(dPin, cPin, MSBFIRST, pin);
  digitalWrite(lPin, HIGH);
 
}
 
 
void blinkAll(int n, int d) {
  digitalWrite(lPin, LOW);
  shiftOut(d, cPin, MSBFIRST, 0);
  digitalWrite(lPin, HIGH);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(lPin, LOW);
    shiftOut(dPin, cPin, MSBFIRST, 255);
    digitalWrite(lPin, HIGH);
    delay(d);
    digitalWrite(lPin, LOW);
    shiftOut(dPin, cPin, MSBFIRST, 0);
    digitalWrite(lPin, HIGH);
    delay(d);
  }
}
  
