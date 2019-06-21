#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
 
void setup() {
  lcd.begin(16, 2); //Deklaracja typu
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Witaj na");
  lcd.setCursor(0,1);
  lcd.print("FORBOT.pl"); 
}
int jasnosc = 0;    
int zmiana = 5;   
 
void loop()
{
  analogWrite(11, jasnosc); //Generuj sygnał PWM o zadanym wypełnieniu   
  jasnosc = jasnosc + zmiana; //W następnym obiegu zmien jasnosc o wartosc zmiennej zmiana
 
  if (jasnosc == 0 || jasnosc == 255) { //Jeśli wypełnienie to 0% lub 100%
    zmiana = 0-zmiana; //To zmień znak zmiany (zacznij zmieniać w przeciwną stronę)
  }     
   
  delay(30); //Czekaj dla lepszego efektu    
}
