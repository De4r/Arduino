int latchPin = 7;
int dataPin = 8;
int clockPin = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 63);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 6);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 91);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 79);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 102);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 109);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 125);
  digitalWrite(latchPin, HIGH);
  
  delay(1000);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 7);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 127);
  digitalWrite(latchPin, HIGH);
  delay(1000);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 103);
  digitalWrite(latchPin, HIGH);
  delay(1000);
  
  
  
}
