#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <RF24Network.h>
#include <RF24Network_config.h>
#include <Sync.h>
#include <Wire.h>
#include <RF24.h>
#include <SPI.h>

// Sender Code
/*
 * PINs and connections
 * nRF2401L module with UNO
 *        none -  IRQ 7 8 MISO - D12 (MISO)
 *  D11 (MOSI) - MOSI 5 6 SCK  - D13 (SCK)
 *    D10 (SS) -  SCN 3 4 CE   - D9
 *       3,3V  -  Vcc 1 2 GND  - GND
 *
 *  NANO verison :
 *  3,3V - VCC, GND-GND
 *  SCL(A5), SDA(A4)
 *  
 *  nFR2401L module with NANO
 *        none -  IRQ 7 8 MISO - D12 (MISO)
 *  D11 (MOSI) - MOSI 5 6 SCK  - D13 (SCK)
 *    D10 (SS) -  SCN 3 4 CE   - D9
 *       3,3V  -  Vcc 1 2 GND  - GND
 *       
 *  I2C level shifter required to shift 5V I2C rail to 3,3V
 *  BMP280 Wiring 
 *   3,3V - Vcc, GND - GND, SCL_3,3V - SCL,  SDA_3,3V - SDA
 *  BH1750 Wiring
 *   3,3V - Vcc, GND - GND, SCL_3,3V - SCL,  SDA_3,3V - SDA
 */
// Data correction :
float tempCorrection = 1.715; // For 3rd module 1.03, for 1st module 1.715, for 2nd module 1.325

// Adresses of all nodes: 00 - master node, 01-04 - 1st lvl child nodes
const uint16_t nof = 3; // number of nodes
const uint16_t node_address_set[nof] = {00, 01, 02};
uint8_t NODE_ADDRESS = 1; // Selecting actual node adress
const uint16_t this_node = node_address_set[NODE_ADDRESS]; 

Adafruit_BMP280 bmp; // I2C
BH1750 lightMeter;
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network

float data[4] = {NODE_ADDRESS, 0, 0, 0};
bool asked = 0;

unsigned long interval = 10000; // ms   
unsigned long last_time_sent;

void setup() {
  // Start 3 interfaces
  Serial.begin(115200);
  Wire.begin();
  SPI.begin();
  
  // Starting radio and network - not set low power yet
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  // Starting lightMeter with one time measurement mode
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
//  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  // Starting bmp280
  if (!bmp.begin(0x76)) {
    if (!bmp.begin(0x77)) {
      Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
      while (1);
    }
  }
  
  // Setting bmp280: at the time normal mode, dont care about power
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering.  OFF - no continous measurements*/
                  Adafruit_BMP280::STANDBY_MS_2000); /* Standby time. */

  // begin node in the network!
  network.begin(90, this_node); //(channel, node address)

  // First readings!
  readData();
}


void loop() {
  // update network 
  network.update();
  // if available then read
  while (network.available()){
    RF24NetworkHeader header;
    network.read(header, &interval, sizeof(interval)); // Read the incoming data
    asked = 1;
  }
  
  // Checking if interval passed ( will be changed to ask for measurement
  if (millis() - last_time_sent > interval || asked == 1){
    readData();
    
    RF24NetworkHeader header(node_address_set[0]); // wrtie header to master base
    bool ok = network.write(header, &data, sizeof(data)); // write data
    if (Serial){
      if (ok==true){
        Serial.println("Send package");
      }
      printData();
    }
    last_time_sent = millis();
    asked = 0;
  }
  
}

void readData(){
  data[3] = lightMeter.readLightLevel(); // acquire the light level
  data[1] = bmp.readTemperature() - tempCorrection; // acquire temperature
  data[2] = bmp.readPressure()/100.0; // accquire pressure level
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

/*
 * Additional things to use
 * include <avr/pgmspace.h>
 * include <avr/sleep.h>
 * include <avr/power.h>
 * typedef enum { wdt_16ms = 0, wdt_32ms, wdt_64ms, wdt_128ms, wdt_250ms, wdt_500ms, wdt_1s, wdt_2s, wdt_4s, wdt_8s } wdt_prescalar_e;
 * 
 * unsigned long awakeTime = 500;                          // How long in ms the radio will stay awake after leaving sleep mode
 * unsigned long sleepTimer = 0;                           // Used to keep track of how long the system has been awake
 *
*/
