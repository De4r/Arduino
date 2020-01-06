#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;
void readLightLevelsAvg(int burst=0);

const int n = 3;
const int lastMeas = 3;
float data[n];
float dataArray[n][lastMeas];
int pins[n] = {7, 6, 5};

// Delay manager to send pings regularly. Because of sleepNode(), this is largely irrelevant.

unsigned long Ts = 5000; // ms
unsigned long interval = Ts - n*200; // ms
unsigned long last_time_sent;

bool readed = 0;
// This sketch is to measure light level with few BH1750 and log them to csv
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
//  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE_2);
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
//  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  for (int i; i<n; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }
//  readLightLevels();
//  last_time_sent = millis();
  if (lastMeas>1) fillUp();
}


void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - last_time_sent > interval) && (readed == 0)){
      readLightLevels();
//      readLightLevelsAvg();

      readed = 1;
    }
    
    if ((millis() - last_time_sent > Ts) && (readed == 1)){
      printData();
      readed = 0;
      last_time_sent = millis();
    }

}

// once read to data buffer
void readLightLevels(){
  for (int i=0; i<n; i++) {
    digitalWrite(pins[i], LOW);
    delayMicroseconds(75);
    data[i] = lightMeter.readLightLevel();
    delayMicroseconds(25);
    digitalWrite(pins[i], HIGH);
  }
}

// printing to serial
void printData(){
  for (int i=0; i<n-1; i++) {
    Serial.print(data[i]);
    Serial.print(",");
  }
  int i = n-1;
  Serial.println(data[i]);
}

// shift last measurements, read new and calc data to output
void readLightLevelsAvg(int burst=0){
  shiftValues();
  if (burst == 0){
    for (int i=0; i<n; i++) {
      digitalWrite(pins[i], LOW);
      delayMicroseconds(75);
      dataArray[i][0] = lightMeter.readLightLevel();
      delayMicroseconds(25);
      digitalWrite(pins[i], HIGH);
    }
  }
  else if (burst == 1) fillUp();
  calcOutput();
}

// shifts values
void shiftValues(){
  for (int i=lastMeas-1; i>0; i--) {  
    for (int j=0; j<n; j++){
    dataArray[j][i] = dataArray[j][i-1];
   }
  }
}

// calcs average
void calcOutput(){
  for (int j=0; j<n; j++) {
    float temp = 0;
    for (int i=0; i<lastMeas; i++) {  
      temp += dataArray[j][i];
    }
    data[j] = temp/lastMeas;
  }
}

// fills first values
void fillUp(){
    for (int i=0; i<lastMeas; i++) {  
       for (int j=0; j<n; j++) {
          digitalWrite(pins[j], LOW);
          delayMicroseconds(75);
          dataArray[j][i] = lightMeter.readLightLevel();
          delayMicroseconds(25);
          digitalWrite(pins[j], HIGH);
      }
    }
}
