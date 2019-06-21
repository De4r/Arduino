#include <Servo.h>
Servo servo;
int pozycja = 0;
int zmiana = 6;
void setup() {
  // put your setup code here, to run once:
  servo.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (pozycja < 180 ) {
    servo.write(pozycja);
  } else {
    pozycja = 0;
  }
  pozycja = pozycja + zmiana;
  delay(200);
}
