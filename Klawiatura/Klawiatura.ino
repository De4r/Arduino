#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 8, 9};

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
LiquidCrystal_I2C lcd(0x27, 16, 2);
Keypad klawiatura = Keypad (makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
  lcd.print("Start ... ..");
  lcd.blink();
}

void loop() {
  // put your main code here, to run repeatedly:
  char klawisz = klawiatura.getKey();
  if (klawisz){
    Serial.println(klawisz);
    lcd.home();
    lcd.clear();
    lcd.print(klawisz);
  }
}
