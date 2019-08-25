#define DATA 11
#define SHIFT 9
#define STORE 10

void store();
int pic[] = {0,36,36,36,0,66,60,0};

void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(SHIFT, OUTPUT);
  pinMode(STORE, OUTPUT);
}

void loop() {
  for (int i=0; i<8; i++) {
    shiftOut(DATA, SHIFT, LSBFIRST, ~pic[i]);
    shiftOut(DATA, SHIFT, LSBFIRST, 128 >> i);
    store();
  }
}

void store() {
  digitalWrite(STORE, HIGH);
  delayMicroseconds(10);
  digitalWrite(STORE, LOW);
  delayMicroseconds(10);
}
