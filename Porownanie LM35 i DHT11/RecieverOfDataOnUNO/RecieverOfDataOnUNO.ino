#include <RH_ASK.h>
#include <SPI.h>

String strHumidDHT;
String strTempDHT;
String strTempLM35;
String strIn;
String bin;
bool breakTig = false;
float floTempDHT;
float floHumidDHT;
float floTempLM35;

RH_ASK rf_driver;

void setup() {
  // put your setup code here, to run once:
  rf_driver.init();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buffor[17];
  uint8_t bufforLen = sizeof(buffor);
  // buffor jako tablica, i jego dlugosc, petla oczekiwania na widomosc
    
  if (rf_driver.recv(buffor, &bufforLen))
  {
    strIn = String((char*)buffor);
    for (int i = 0; i < strIn.length(); i++) 
    { 
      if (strIn.substring(i, i + 1) == ",")
      {
        strHumidDHT = strIn.substring(0, i);
        bin = strIn.substring(i + 1);
        
        for ( int j = 0; j < bin.length(); j++)
        { 
          
          if (bin.substring(j, j + 1) == ",")
          {
            strTempDHT = bin.substring(0, j);
            strTempLM35 = bin.substring(j + 1);
            
            breakTig = true;
            break;
                        
          }
        }
        if ( breakTig == true )
        {
          breakTig = false;
          break;
        }
      }
    }
       
    floHumidDHT = atof(strHumidDHT.c_str());
    floTempDHT = atof(strTempDHT.c_str());
    floTempLM35 = atof(strTempLM35.c_str());
    
    Serial.print("Humidity:");
    Serial.print(floHumidDHT);
    Serial.print(",Temperature DHT:");
    Serial.print(floTempDHT);
    Serial.print(",Temperature LM:");
    Serial.println(floTempLM35);
  }
  

}
