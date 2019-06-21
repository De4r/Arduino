#define pn 8
#define pc 9
#define s 10
#define lc 11
#define ln 12

int lfoto = 0;
int lfotomap = 0;
int pfotomap = 0;
int pfoto = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pn, OUTPUT);
  pinMode(pc, OUTPUT);
  pinMode(s, OUTPUT);
  pinMode(lc, OUTPUT);
  pinMode(ln, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lfoto = analogRead(A4);
  pfoto = analogRead(A5);
  Serial.println("Lewy fotorezystor :");
  Serial.println(lfoto);
  Serial.println("Prawy fotorezystor :");
  Serial.println(pfoto);
  delay(250);
  lfotomap = map(lfoto,300,1010, 1, 5);
  pfotomap = map(pfoto,300,1010, 1, 5);
  if (lfotomap == 5) {
    digitalWrite(ln, HIGH);
    digitalWrite(lc, LOW);
    digitalWrite(s, LOW);
    digitalWrite(pc, LOW);
    digitalWrite(pn, LOW);
  } else if ( pfotomap == 5 ) {
    digitalWrite(ln, LOW);
    digitalWrite(lc, LOW);
    digitalWrite(s, LOW);
    digitalWrite(pc, LOW);
    digitalWrite(pn, HIGH);
  } else if (pfotomap == lfotomap ) {
    digitalWrite(ln, LOW);
    digitalWrite(lc, LOW);
    digitalWrite(s, HIGH);
    digitalWrite(pc, LOW);
    digitalWrite(pn, LOW);
  } else if ( pfotomap > 3 && lfotomap < 3 ) {
    digitalWrite(ln, LOW);
    digitalWrite(lc, LOW);
    digitalWrite(s, LOW);
    digitalWrite(pc, HIGH);
    digitalWrite(pn, LOW);
  } else if ( pfotomap < 3 && lfotomap > 3 ) {
    digitalWrite(ln, LOW);
    digitalWrite(lc, HIGH);
    digitalWrite(s, LOW);
    digitalWrite(pc, LOW);
    digitalWrite(pn, LOW);
  }
}
