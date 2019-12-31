#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <RF24Network.h>
#include <RF24Network_config.h>
#include <Sync.h>
#include <Wire.h>
#include <RF24.h>
#include <SPI.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/power.h>

// Sender Code
/*  Pins and connections
 *  MPU module
 *  NANO verison :
 *  3,3V - VCC, GND-GND
 *  SCL(A5), SDA(A4)
 *  
 *  nFR2401L
 *        none -  IRQ 7 8 MISO - D12 (MISO)
 *  D11 (MOSI) - MOSI 5 6 SCK  - D13 (SCK)
 *    D10 (SS) -  SCN 3 4 CE   - D9
 *       3,3V  -  Vcc 1 2 GND  - GND
 *  */

// Adresses of nodes
const uint16_t node_address_set[10] = { 00, 01, 02};
uint8_t NODE_ADDRESS = 1; // Selecting actual node adress
const uint16_t this_node = node_address_set[NODE_ADDRESS]; 

Adafruit_BMP280 bmp; // I2C
BH1750 lightMeter;
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network

float data[4] = {NODE_ADDRESS, 0, 0, 0};

const unsigned long interval = 5*60000; // ms           // Delay manager to send pings regularly. Because of sleepNode(), this is largely irrelevant.
unsigned long last_time_sent;
//
//typedef enum { wdt_16ms = 0, wdt_32ms, wdt_64ms, wdt_128ms, wdt_250ms, wdt_500ms, wdt_1s, wdt_2s, wdt_4s, wdt_8s } wdt_prescalar_e;
//
//unsigned long awakeTime = 500;                          // How long in ms the radio will stay awake after leaving sleep mode
//unsigned long sleepTimer = 0;                           // Used to keep track of how long the system has been awake

void setup() {
  // Start 3 interfaces
  Serial.begin(115200);
  Wire.begin();
  SPI.begin();
  
  // Starting radio and network - not set low power yet
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_2MBPS);
  // Starting lightMeter with one time measurement mode
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  // Starting bmp280
  if (!bmp.begin(0x77)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  
  // Setting bmp280 to forced mode, x1 reading of temp. and pressure, no IIR
  bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X4,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_OFF,      /* Filtering.  OFF - no continous measurements*/
                  Adafruit_BMP280::STANDBY_MS_4000); /* Standby time. */
  
  network.begin(90, this_node); //(channel, node address)
//  network.setup_watchdog(wdt_1s);

// First readings!
    data[3] = lightMeter.readLightLevel(); // acquire the light level
    data[1] = bmp.readTemperature(); // acquire temperature
    data[2] = bmp.readPressure(); // accquire pressure level
}
void loop() {
  // Checking if interval passed ( will be changed to ask for measurement
  if (millis() - last_time_sent > interval){
    data[3] = lightMeter.readLightLevel(); // acquire the light level
    data[1] = bmp.readTemperature(); // acquire temperature
    data[2] = bmp.readPressure(); // accquire pressure level
    
    RF24NetworkHeader header(node_address_set[0]); // wrtie header to master base
    bool ok = network.write(header, &data, sizeof(data)); // write data
    if (Serial){
      if (ok==true){
        Serial.println("Send package");
      }
      printData();
    }
    last_time_sent = millis();
  }
  
}


void printData(){
  Serial.print(int(data[0]));
  Serial.print(": ");
  Serial.print(data[1]);
  Serial.print(",");
  Serial.print(data[2]);
  Serial.print(",");
  Serial.println(data[3]);
}
