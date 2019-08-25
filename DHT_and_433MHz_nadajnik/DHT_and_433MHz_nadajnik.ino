// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       DHT_and_433MHz_nadajnik.ino
    Created:	25.06.2019 12:26:53
    Author:     MATEUSZ\mkrup
*/

// Define User Types below here or use a .h file
//
#include <RH_ASK.h>
#include <SPI.h>
#include <DHT.h> // do³¹czam bibliotekê od obs³ugi czujnika DHTxx (pamiêtaj ¿eby zainstalowaæ dodatkow¹ bibliotekê Adafruit Unified Sensor Library)


#define DHTPIN 2 // definicja preprocesora
#define DHTTYPE DHT11 // definicja preprocesora


float humidity;
float temperature;

String strHumidity;
String strTemperature;
String strOut;

// Define Function Prototypes that use User Types below here or use a .h file
//


RH_ASK rf_driver(2000, 3, 4); // (predkosc, pin odbiorczy, pin nadwczy)
DHT dht(DHTPIN, DHTTYPE);
// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts

void setup() {
	// put your setup code here, to run once:
	rf_driver.init();
	dht.begin();

}

void loop() {
	// put your main code here, to run repeatedly:

	delay(2000);
	humidity = dht.readHumidity();
	temperature = dht.readTemperature();

	strHumidity = String(humidity);
	strTemperature = String(temperature);
	strOut = strHumidity + "," + strTemperature;

	const char* msg = strOut.c_str();

	rf_driver.send((uint8_t*)msg, strlen(msg));
	rf_driver.waitPacketSent();
	delay(3000);
}
