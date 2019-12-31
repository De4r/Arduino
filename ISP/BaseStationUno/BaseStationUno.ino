#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <RF24Network.h>
#include <RF24Network_config.h>
#include <Sync.h>
#include <RF24.h>
#include <SPI.h>
#include <Wire.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/power.h>


// Reciever Code
/*
 * PINs and connections
 * nRF2401L module with UNO
 *        none -  IRQ 7 8 MISO - D12 (MISO)
 *  D11 (MOSI) - MOSI 5 6 SCK  - D13 (SCK)
 *    D10 (SS) -  SCN 3 4 CE   - D9
 *       3,3V  -  Vcc 1 2 GND  - GND
 */


bool ok;

const uint16_t node_address_set[3] = { 00, 01, 02};
uint8_t NODE_ADDRESS = 0; // Selecting actual node adress
const uint16_t this_node = node_address_set[NODE_ADDRESS]; 

Adafruit_BMP280 bmp; // I2C
BH1750 lightMeter;
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network

float data[3*sizeof(node_address_set)/sizeof(node_address_set)[0]];

bool nodeState[3] = {0, 0, 0};

const unsigned long interval = 5*60000;  //ms  // How often to send data to the other unit
unsigned long last_time;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  SPI.begin();
  
  radio.begin();
  radio.setDataRate(RF24_2MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  // Starting bmp280
  if (!bmp.begin(0x76)) {
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
  Serial.println("Started!");
}
void loop() {
  network.update();
  //===== Receiving =====// 
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    float incData[4];
    network.read(header, &incData, sizeof(incData)); // Read the incoming data
    
//    int j=(int(incData[0])-1)*3;
    int j=(int(incData[0]))*3;
    for (int i=1; i < 4; i++)
    {
      data[j] = incData[i]; j++;
    }
    nodeState[int(incData[0])] = 1;
//    Serial.print("Recieved package from: ");
//    Serial.println(int(incData[0]));
//    nodeState[int(incData[0])-1] = 1;    
  }
  
  if (millis() - last_time > interval){
    data[2] = lightMeter.readLightLevel(); // acquire the light level
    data[0] = bmp.readTemperature(); // acquire temperature
    data[1] = bmp.readPressure(); // accquire pressure level
    last_time = millis();
//    Serial.println("Updated station measurements!");
    nodeState[0] = 1;
  }

  int sum = sumStates();
  if (sum == sizeof(nodeState)/sizeof(nodeState[0])){
    printData();
    setState();
  }
}

void printData(){
  int len = sizeof(data)/sizeof(data[0]);
  for (int i=0; i<len; i++){
    if (i==len-1){
      Serial.println(data[i]);
    } else{
      Serial.print(data[i]);
      Serial.print(",");
    }
  }
}

int sumStates(){
  int sum;
  for (int i=0; i<sizeof(nodeState)/sizeof(nodeState[0]); i++){
    sum += nodeState[i];
  }
//  Serial.print("Summed states: ");
//  Serial.println(sum);
  return sum;
}

void setState(){
  for (int i=0; i<sizeof(nodeState)/sizeof(nodeState[0]); i++){
    nodeState[i] = 0;
  }
//  Serial.println("Setted states to 0");
}
