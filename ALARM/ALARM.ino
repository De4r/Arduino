#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#define BUZZ 11
#define KONT 10
#define PIR 8

int ileCzasuMinelo = 0;
int pinAlarmuPozycja = 1;
char pinCyfra1 = '1';
char pinCyfra2 = '2';
char pinCyfra3 = '3';
char pinCyfra4 = '4';
const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = {3, 2, 1, 0};
byte colPins[COLS] = {4, 5, 6, 7};

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
LiquidCrystal_I2C lcd(0x27, 16, 2);
Keypad klawiatura = Keypad (makeKeymap(keys), rowPins, colPins, ROWS, COLS);

volatile int stanAlarmu = 1;
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.print("Start ... ..");
  lcd.blink();
  pinMode(BUZZ, OUTPUT);
  pinMode(KONT, INPUT_PULLUP);
  pinMode(PIR, INPUT_PULLUP);
  pinMode(A0, OUTPUT); //red
  pinMode(A1, OUTPUT); //green
  pinMode(A2, OUTPUT); //blue
}
char klawisz = 0;
void loop() {
  // put your main code here, to run repeatedly:
  switch(stanAlarmu){
    case 1:
    //czuwanie
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
    lcd.home();
    lcd.clear();
    lcd.print("Czuwanie");
    lcd.blink();
    
    klawisz = klawiatura.getKey();
    if (klawisz == 'A'){
      for (int i=1; i<10; i++){
        digitalWrite(A1, LOW);
        delay(100);
        digitalWrite(A1, HIGH);
      }
      stanAlarmu = 2;
      
    }
    break;

    case 2:
    //monitorowanie
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);//nieb
    delay(50);
    lcd.home();
    lcd.clear();
    lcd.print("Monitorowanie");

    if (digitalRead(PIR) == LOW) {
      stanAlarmu = 4; // Alarm
    } else if (digitalRead(KONT) == HIGH) {
      stanAlarmu = 3; // Czas na rozbrojenie
      ileCzasuMinelo=0;
        pinAlarmuPozycja = 1;
    }
    break;

    case 3:
    // rozbrajanie
    digitalWrite(A0, LOW); // red
    digitalWrite(A1, LOW); 
    digitalWrite(A2, HIGH);//nieb
    lcd.home();
    lcd.clear();
    lcd.print("Wpisz Pin");
    klawisz = klawiatura.getKey();
    if (klawisz) {
      if (pinAlarmuPozycja == 1 && klawisz == pinCyfra1) { //Jesli sprawdzamy 1 pozycje PINu
          pinAlarmuPozycja++; //Cyfra poprawna, mozna sprawdzic na kolejna
        } else if (pinAlarmuPozycja == 2 && klawisz == pinCyfra2) { //Jesli sprawdzamy 2 pozycje PINu
          pinAlarmuPozycja++; //Cyfra poprawna, mozna sprawdzic na kolejna         
        } else if (pinAlarmuPozycja == 3 && klawisz == pinCyfra3) { //Jesli sprawdzamy 3 pozycje PINu
          pinAlarmuPozycja++; //Cyfra poprawna, mozna sprawdzic na kolejna        
        } else if (pinAlarmuPozycja == 4 && klawisz == pinCyfra4) { //Jesli sprawdzamy 4 pozycje PINu
            stanAlarmu = 1; //Wszystkie 4 cyfry kodu sa poprawne      
        } else {
           stanAlarmu = 4; //Blad w kodzie PIN - wlacz alarm
    }
    }
    delay(100);
    ileCzasuMinelo++;

    if (ileCzasuMinelo >= 50){
      stanAlarmu = 4;
    }
    break;

    case 4:
    //sygnalizacja alarmu
    digitalWrite(A0, HIGH); //czerwona
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    lcd.home();
    lcd.clear();
    lcd.print("ALARM !!!");
    lcd.blink();
    tone(BUZZ, 3500, 200);
    delay(100);
    klawisz = klawiatura.getKey();
    if (klawisz) {
      if (klawisz == 'B') {
        delay(300);
        ileCzasuMinelo=0;
        pinAlarmuPozycja = 1;
      stanAlarmu = 3;
    }
  }
    break;

    
}
}
