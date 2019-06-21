#define P1 8
#define P2 9
#define P3 10
#define P4 11

void setup() {
  // put your setup code here, to run once:
  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  pinMode(P4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i< 500; i++) {
    motor_CW (2);
  }
  for (int i=0; i<500; i++) {
    motor_CCW(2);
  }
}

void motor_CW (int dly)
{
  digitalWrite(P1, HIGH);
  delay(dly);
  digitalWrite(P1, LOW);
  digitalWrite(P2, HIGH);
  delay(dly);
  digitalWrite(P2, LOW);
  digitalWrite(P3, HIGH);
  delay(dly);
  digitalWrite(P3, LOW);
  digitalWrite(P4, HIGH);
  delay(dly);
  digitalWrite(P4, LOW);
  
}

void motor_CCW( int dly)
{
  digitalWrite(P4, HIGH);
  delay(dly);
  digitalWrite(P4, LOW);
  digitalWrite(P3, HIGH);
  delay(dly);
  digitalWrite(P3, LOW);
  digitalWrite(P2, HIGH);
  delay(dly);
  digitalWrite(P2, LOW);
  digitalWrite(P1, HIGH);
  delay(dly);
  digitalWrite(P1, LOW);
  
}
