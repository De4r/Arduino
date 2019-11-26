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
 */
#include <SPI.h>
#include "RF24.h"
#include <Wire.h>

long accX, accY, accZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotatX, rotatY, rotatZ;

float dataToTransmit[7];
float freq = 100; // microseconds between points
unsigned long time1=0, time2=0;

RF24 radio(9, 10); // Pins on arduino nano : D9 (CE) D10 (SS/ CSN)
const uint64_t pipeName = 0x123456789ABC; // Code for pairing
int dataTransmitted; // Data to transmite

void setup() {
  // put your setup code here, to run once:
  
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(110);
  radio.openWritingPipe(pipeName);
  Wire.begin();
  Wire.setClock(400000);
  setupMPU();
  radio.powerUp();

}

void loop() {
  // put your main code here, to run repeatedly:
  time1=micros();
  if (time1-time2 >= freq){
    recordAccelRegisters();
    recordGyroRegisters();
    dataToTransmit[6] = time1/1000000.0;
    //radio.powerUp();
    radio.write(&dataToTransmit, sizeof(dataToTransmit));
    //radio.powerDown();
    time2=time1;
    
  }
  
  
}

void setupMPU() {
  Wire.beginTransmission(0b1101000); // adres przy AD0 podlaczonego do GND
  Wire.write(0x6B); // adres odpowiedzialny za ustawienia zasilania
  Wire.write(0b00000000);
  Wire.endTransmission();
  
  Wire.beginTransmission(0b1101000); // adres przy AD0 podlaczonego do GND
  Wire.write(0x1B); // adres odpowiedzialny za ustawienia zyroskopu
  Wire.write(0b00000000); // zyroskop w zakresie +/- 250 deg/sec
  Wire.endTransmission();
  
  Wire.beginTransmission(0b1101000); // adres przy AD0 podlaczonego do GND
  Wire.write(0x1C); // adres odpowiedzialny za ustawienia akcelerometrow
  Wire.write(0b00000000); // akcelerometry w zakresie +/- 2 g       bit 8 7 6 5 4 3 2 1
  Wire.endTransmission();
    
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B); // adres rejestru pomiarow przyspieszenia
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //odczyt z magistrali i2c 6 bitow
  while(Wire.available() < 6);
  accX = Wire.read()<<8|Wire.read(); // pierwsze 2 bajt sa w X
  accY = Wire.read()<<8|Wire.read(); // kolejne 2
  accZ = Wire.read()<<8|Wire.read();
  processAccelData();
  
}

void processAccelData() {
  dataToTransmit[0] = accX / 16384.0 * 9.81;
  dataToTransmit[1] = accY / 16384.0 * 9.81;
  dataToTransmit[2] = accZ / 16384.0 * 9.81;
   
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43); // adres rejestru pomiarow przyspieszenia
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //odczyt z magistrali i2c 6 bitow
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); // pierwsze 2 bajt sa w X
  gyroY = Wire.read()<<8|Wire.read(); // kolejne 2
  gyroZ = Wire.read()<<8|Wire.read();
  processGyroData();
  
}

void processGyroData() {
  dataToTransmit[3] = gyroX / 131.0;
  dataToTransmit[4] = gyroY / 131.0;
  dataToTransmit[5] = gyroZ / 131.0;
}
