#define LM35 A5
void setup() {
  Serial.begin(9600); //Prędkość transmisji w porcie szeregowym
  }

void loop() {
  float temperatura;
 temperatura = analogRead(LM35); //Odczytanie napięcia z czujnika temperatury
 temperatura = temperatura * 0.48828125; //Wyznaczenie temperatury



//Dodatkowe wyświetlenie temperatury w serial port
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
   
   delay(1000); //Odświeżanie co 1 sekundę
}
