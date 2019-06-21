#define przycisk 9
#define zolta 10
#define nieb 11
#define czerw 12

String dane = "";
int dane_int = 0;
int licz = 0;
int odcz = 0;
int blad = 50;
boolean start = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(przycisk, INPUT_PULLUP);
  pinMode(zolta, OUTPUT);
  pinMode(nieb, OUTPUT);
  pinMode(czerw, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( start = true ) {
    licz = 3;
    digitalWrite(zolta, LOW);
    digitalWrite(nieb, LOW);
    digitalWrite(czerw, LOW);
    
    while (!Serial) delay(10);
    Serial.println("Przekrec potencjometr i nacisnij przycisk");
    delay(250);
    while (digitalRead(przycisk) == HIGH) delay(50);
    odcz = analogRead(A5);
    while ( licz != -1){
      Serial.println("Podaj liczbe z zakresu 0-1023");
      
      while (Serial.available() == 0);
      dane = Serial.readStringUntil('\n');
      dane_int = dane.toInt();
      
      if (odcz + blad > dane_int && odcz - blad < dane_int ) {
        Serial.println("wygrales");
        Serial.println(odcz);
        digitalWrite(nieb, HIGH);
        start = true;
        delay(200);
        Serial.println("Jesli chcesz zagrac nacisnij przycisk");
        while (digitalRead(przycisk) == HIGH) delay(20);
        break;
        digitalWrite(zolta, LOW);
        digitalWrite(czerw, LOW);
        
      } else {
        if (licz > 0) {
          start = false;
          digitalWrite(zolta, HIGH);
          Serial. println("Spróboj jeszcze raz");
          Serial.println("Pozostało Ci jeszcze: ");
          Serial.println(licz);
          Serial.println("prob");
          licz = licz - 1;
        } else if (licz == 0) {
          Serial.println(odcz);
          digitalWrite(czerw, HIGH);
          Serial.println("Przegrałes. Jescze raz? nacisnij przycisk");
          delay(250);
          while (digitalRead(przycisk) == HIGH) start = true; 
          delay(200);
          break;     
       }
       }
      }

    }
  }
