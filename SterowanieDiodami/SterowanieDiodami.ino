#define zolta 8
#define nieb 9
boolean niebStan = false;
boolean zoltaStan = false;
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
      zoltaStan =! zoltaStan;
    } else if (odebraneDane == "niebieska") {
      niebStan =! niebStan;
    }
    if (odebraneDane != "niebieska" && odebraneDane != "zolta") {
      Serial.println("Podaj poprawny kolor! (niebieska/ zolta)");
    }
    digitalWrite(zolta, zoltaStan);
    digitalWrite(nieb, niebStan);
  }
}
