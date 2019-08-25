// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       ArduinoMicroTest.ino
    Created:	23.06.2019 17:23:23
    Author:     MATEUSZ\mkrup
*/

// Define User Types below here or use a .h file
//
#define LED 13
int x = 0;

// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);
	Serial.println("Welcome to the Visual Micro Demo");
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);


}

// Add the main program code into the continuous loop() function
void loop()
{
	digitalWrite(LED, LOW);
	delay(2000);

	Serial.print("Break point reached: x = ");
	Serial.println(x);

	digitalWrite(LED, HIGH);
	delay(2000);
	x++;
	if (x > 9) {
		x = 0;
	}
}
