const int SER = 8;
const int RCLK = 9;
const int SRCLK = 10;

int seq[14] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2};

void setup() {
  // put your setup code here, to run once:
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<14; i++) {
    digitalWrite(RCLK, LOW);
    shiftOut(SER, SRCLK, MSBFIRST, seq[i]);
    digitalWrite(RCLK, HIGH);
    delay(500);
  }
}
