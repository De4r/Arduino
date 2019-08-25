#include <DHT.h> // dołączam bibliotekę od obsługi czujnika DHTxx (pamiętaj żeby zainstalować dodatkową bibliotekę Adafruit Unified Sensor Library)

#define DHTPIN 11 // definicja preprocesora
#define DHTTYPE DHT11 // definicja preprocesora

DHT dht(DHTPIN, DHTTYPE);

float humid;
float temp;

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  Serial.begin(9600);
  delay(3000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  humid = dht.readHumidity();
  temp = dht.readTemperature();

  
  Serial.print(humid);
  Serial.print(",");
  Serial.println(temp);
  delay(60000);
}
