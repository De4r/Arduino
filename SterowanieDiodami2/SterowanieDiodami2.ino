#define zielona 8
#define czerwona 9

String odebraneDane = "";
boolean stanCzerwonej = false;
boolean stanZielonej = false;

void setup() {
 Serial.begin(9600); 
 pinMode(zielona, OUTPUT);
 pinMode(czerwona, OUTPUT);

 digitalWrite(zielona, LOW);
 digitalWrite(czerwona, LOW);
}

void loop() {
 if(Serial.available() > 0) { 
   odebraneDane = Serial.readStringUntil('\n'); 

   if (odebraneDane == "zielona") {
     stanZielonej = !stanZielonej;
   }

   if (odebraneDane == "czerwona") {
     stanCzerwonej = !stanCzerwonej;
   }

   if (odebraneDane != "czerwona" && odebraneDane != "zielona") {
     Serial.println("Nieprawidlowy kolor! Wpisz 'zielona' lub 'czerwona'.");
   }

   digitalWrite(zielona, stanZielonej);
   digitalWrite(czerwona, stanCzerwonej);
 }

}
