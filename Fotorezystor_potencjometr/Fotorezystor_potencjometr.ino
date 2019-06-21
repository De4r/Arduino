int odcz = 0;
int prog = 0;
boolean druk = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  odcz = analogRead(A5);
  prog = analogRead(A4);
  
  
  if (odcz < prog) {
    digitalWrite(8, HIGH);
    if (druk == true) {
      Serial.println("Odczyt: " + String(odcz));
      Serial.println("Prog: " + String(prog));
      druk = false;
    }
  } else {
    digitalWrite(8, LOW);
    druk = true;
  }
  delay(100);
} 
