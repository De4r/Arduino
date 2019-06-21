int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int delayTime = 10;

// usuń komentarz dla diody ze wspólną anodą
#define COMMON_ANODE

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 256; i++) {
    setColor(255 - i, i, 0);
    delay(delayTime);
  }
  
  for (int i = 0; i < 256; i++) {
    setColor(0, 255 - i, i);
    delay(delayTime);
  }
  
  for (int i = 0; i < 256; i++) {
    setColor(i, 0, 255 - i);
    delay(delayTime);
  }
}

void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
