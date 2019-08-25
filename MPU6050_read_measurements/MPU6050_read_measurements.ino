#include <Wire.h>

long accX, accY, accZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotatX, rotatY, rotatZ;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
}

void loop() {
  // put your main code here, to run repeatedly:
  recordAccelRegisters();
  recordGyroRegisters();
  printData();
  delay(100);
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
  gForceX = accX / 16384.0;
  gForceY = accY / 16384.0;
  gForceZ = accZ / 16384.0;
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
  rotatX = gyroX / 131.0;
  rotatY = gyroY / 131.0;
  rotatZ = gyroZ / 131.0;
}

void printData(){
  //Serial.print("Gyro [deg]: ");
  //Serial.print("X=");
  Serial.print(rotatX);
  Serial.print(",");
  Serial.print(rotatY);
  Serial.print(",");
  Serial.print(rotatZ);
  
  Serial.print(",");
  Serial.print(gForceX);
  Serial.print(",");
  Serial.print(gForceY);
  Serial.print(",");
  Serial.println(gForceZ);
}
