int mic=2;
int lampka=8;
boolean lastMic=LOW;
boolean nowMic=LOW;
boolean lampON=false;

void setup() {
  // put your setup code here, to run once:
  pinMode(mic, INPUT);
  pinMode(lampka, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  nowMic = digitalRead(mic);
  if ( lastMic==LOW && nowMic==HIGH) {
    lampON = !lampON;
  }
  lastMic = nowMic;
  digitalWrite(lampka, lampON);
  
}
