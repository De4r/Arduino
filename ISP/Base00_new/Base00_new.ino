#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <RF24Network.h>
#include <RF24Network_config.h>
#include <Sync.h>
#include <RF24.h>
#include <SPI.h>
#include <Wire.h>


// Reciever Code
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
float tempCorrection = 1.03; // For 3rd module 1.03, for 1st module 1.715, for 2nd module 1.325

// Adresses of all nodes: 00 - master node, 01-04 - 1st lvl child nodes
const uint16_t nof = 3; // number of nodes
const uint16_t node_address_set[nof] = { 00, 01, 02};
uint8_t NODE_ADDRESS = 0; // Selecting actual node adress
const uint16_t this_node = node_address_set[NODE_ADDRESS]; 

Adafruit_BMP280 bmp; // I2C
BH1750 lightMeter;
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network

const int vpn = 3; // Values measured per node + 1 for node number!
float data[3*nof]; // Allocate memory for data

bool start = 0; // start measures
bool ok; // state check
bool nodeState[nof]; // Vector of states

unsigned long interval = 10000;  //ms  // How often to send data to the other unit
unsigned long last_time;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  SPI.begin();
  
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
  
  // Setting bmp280 to forced mode, x1 reading of temp. and pressure, no IIR
 bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering.  OFF - no continous measurements*/
                  Adafruit_BMP280::STANDBY_MS_2000); /* Standby time. */
                  
  network.begin(90, this_node); //(channel, node address)
  
}


void loop() {
  network.update();
  if (nodeState[0] == 1){
    //===== Receiving =====// 
    while ( network.available()) {     // Is there any incoming data?
      RF24NetworkHeader header;
      float incData[4];
      network.read(header, &incData, sizeof(incData)); // Read the incoming data
      
      // fill data on proper indexes
      int j=(int(incData[0]))*vpn; // get the j = nof*3 as 1st index
      if (j != 0){
        for (int i=1; i < vpn+1; i++)
        {
          data[j] = incData[i]; j++;
        }
        nodeState[int(incData[0])] = 1;
      } else {
        askForData();
      }
  }
    
  if (millis() - last_time > interval || start == 1){
    readData();
    last_time = millis();
//    Serial.println("Updated station measurements!");
    nodeState[0] = 1;
      
    askForData();
    
    if (start == 1) start = 0;
   
  }
  if (Serial.available() > 0) {
    // read the incoming byte:
    String inString = Serial.readString();
    interval = (unsigned long)inString.toInt();
  }

  int sum = sumStates();
  if (sum == nof){
    printData();
    setState();
  }
}



 // Funcstions!
void readData(){
  data[2] = lightMeter.readLightLevel(); // acquire the light level
  data[0] = bmp.readTemperature() - tempCorrection; // acquire temperature
  data[1] = bmp.readPressure()/100.0; // accquire pressure level
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
  for (int i=0; i<nof; i++){
    sum += nodeState[i];
  }
//  Serial.print("Summed states: ");
//  Serial.println(sum);
  return sum;
}

void setState(){
  for (int i=0; i<nof; i++){
    nodeState[i] = 0;
  }
//  Serial.println("Setted states to 0");
}

void askForData() {
  RF24NetworkHeader header1(node_address_set[1]); // write header to node
  bool oks1 = network.write(header1, &interval, sizeof(interval)); // write data
//  Serial.println(oks1);
    
  RF24NetworkHeader header2(node_address_set[2]); // write header to node
  bool oks2 = network.write(header2, &interval, sizeof(interval)); // write data
//  Serial.println(oks2);
}
