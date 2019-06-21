const int data = 4;
const int shift = 3;
const int store = 2;
const int R1 = 12;
const int R2 = 11;
const int R3 = 10;
const int R4 = 9;
const int R5 = 8;
const int R6 = 7;
const int R7 = 6;
const int R8 = 5;
int i=0;
int seq[8] = {1,2,4,8,16,32,64,128};
char row[8] = {R1,R2,R3,R4,R5,R6,R7,R8};

void setup() {
  // put your setup code here, to run once:
  pinMode(data, OUTPUT);
  pinMode(shift, OUTPUT);
  pinMode(store, OUTPUT);
  for (int i=0; i<8; i++) {
    pinMode(row[i], OUTPUT);
    digitalWrite(row[i], HIGH);
  }
  digitalWrite(shift, LOW);
  shiftOut(data, store, MSBFIRST, 0);
  digitalWrite(shift, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for (int i=0;i<8; i++) {
    digitalWrite(row[i], LOW);
    for (int j=0; j<8; j++) {
      digitalWrite(shift, LOW);
      shiftOut(data, store, MSBFIRST, seq[j]);
      digitalWrite(shift, HIGH);
      delayMicroseconds(10);
    }
//    delayMicroseconds(30);
    digitalWrite(row[i], HIGH);
  }
  


}
