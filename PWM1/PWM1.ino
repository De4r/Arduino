#define dioda 3
byte wypelnienie = 5;
int zmiana = 5;
boolean inv = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(dioda, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(dioda, wypelnienie);
  if ( wypelnienie <= 255 && inv == false ) {
    wypelnienie = wypelnienie + zmiana;
    if ( wypelnienie == 255) {
      inv = true;
    }
  } else {
    wypelnienie = wypelnienie - zmiana;
    if (wypelnienie == 0) {
      inv = false;
    }
  }
  delay(50);
}
