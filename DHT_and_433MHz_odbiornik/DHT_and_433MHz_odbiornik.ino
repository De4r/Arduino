// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       DHT and 433MHZ.ino
    Created:	25.06.2019 12:13:37
    Author:     MATEUSZ\mkrup
*/

// Define User Types below here or use a .h file
//
#include <RH_ASK.h>
#include <SPI.h>


// Define Function Prototypes that use User Types below here or use a .h file
//
RH_ASK rf_driver;

String strHumidity;
String strTemperature;
String strIn;
float floHumid;
float floTemp;

// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts



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
	if (rf_driver.recv(buffor, &bufforLen))
	{
		strIn = String((char*)buffor);

		for (int i = 0; i < strIn.length(); i++) {
			if (strIn.substring(i, i + 1) == ",") {
				strHumidity = strIn.substring(0, i);
				strTemperature = strIn.substring(i + 1);
				break;

			}
		}


		Serial.print("Humidity: ");
		Serial.print(strHumidity);
		Serial.print("         Temperature: ");
		Serial.println(strTemperature);
		floHumid = atof(strHumidity.c_str());
		floTemp = atof(strTemperature.c_str());

		Serial.print("Humidity: ");
		Serial.print(floHumid);
		Serial.print("         Temperature: ");
		Serial.println(floTemp);
	}

}

