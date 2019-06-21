int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int delayTime = 1000;

// usuń komentarz dla diody ze wspólną anodą
#define COMMON_ANODE

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  setColor(255, 0, 0);  // red
  delay(delayTime);
  setColor(0, 255, 0);  // green
  delay(delayTime);
  setColor(0, 0, 255);  // blue
  delay(delayTime);
  setColor(255, 255, 0);  // yellow
  delay(delayTime);
  setColor(80, 0, 80);  // purple
  delay(delayTime);
  setColor(0, 255, 255);  // aqua
  delay(delayTime);
  setColor(0xae, 0xdb, 0x46);  // custom green
  delay(delayTime);
  setColor(0xffb52d);  // custom orange
  delay(delayTime);
  setColor(0x49ffd1);  // custom blue
  delay(delayTime);
  setColor(0xec9bff);  // custom pink
  delay(delayTime);
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

void setColor(unsigned long hexColor) {
  setColor((hexColor & 0xff0000) >> 16, (hexColor & 0x00ff00) >> 8, hexColor & 0x0000ff);
}
