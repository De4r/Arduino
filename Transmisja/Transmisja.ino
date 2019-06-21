#define zolta 8
#define nieb 9
String odebraneDane ="";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Connecteed");
  pinMode(zolta, OUTPUT);
  pinMode(nieb, OUTPUT);
  
  digitalWrite(zolta, LOW);
  digitalWrite(nieb, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    odebraneDane = Serial.readStringUntil('\n');

    if (odebraneDane == "zolta") {
      digitalWrite(zolta, HIGH);
      delay(1000);
      digitalWrite(zolta, LOW);
    }
    
    if (odebraneDane == "niebieska") {
      digitalWrite(nieb, HIGH);
      delay(1000);
      digitalWrite(nieb, LOW);
    } else {
      Serial.println("Podaj poprawny kolor! (niebieska/ zolta)");
    }
    
  }
}
