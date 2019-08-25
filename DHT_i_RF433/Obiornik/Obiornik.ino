#include <RH_ASK.h>
#include <SPI.h>

String strHumidity;
String strTemperature;
String strIn;

float temp;
float humid;

RH_ASK rf_driver;

void setup() {
  // put your setup code here, to run once:
  rf_driver.init();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buffor[11];
  uint8_t bufforLen = sizeof(buffor);
  // buffor jako tablica, i jego dlugosc, petla oczekiwania na widomosc
  if  ( rf_driver.recv(buffor, &bufforLen))
  {
    strIn = String((char*)buffor);

    for (int i = 0; i < strIn.length(); i++) {
      if (strIn.substring(i, i+1) == ",") {
        strHumidity = strIn.substring(0,i);
        strTemperature = strIn.substring(i+1);
        break;
        
      }
    }
    
  
  Serial.print("Humidity: ");
  Serial.print(strHumidity);
  Serial.print("         Temperature: ");
  Serial.println(strTemperature);

  temp = atof(strTemperature.c_str());
  humid = atof(strHumidity.c_str());
  Serial.print("Humidity: ");
  Serial.print(humid);
  Serial.print("         Temperature: ");
  Serial.println(temp);
  }
  
}
