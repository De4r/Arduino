byte speedLevel=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, OUTPUT); // piny 1 2 3 4 motory przod
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  
  pinMode(7, OUTPUT); // piny 1 2 3 4 motory tyl
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(3, OUTPUT); // pwm motor a przod
  pinMode(9, OUTPUT); // pwm motor b przod
  pinMode(10, OUTPUT); // pwm motor a tył
  pinMode(11, OUTPUT); // pwm motor b tył

 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Forward");
  for (int i = 50; i<200; i++) {
    speedLevel = i;
    driveForward();
    delay(100);
  }
  stopCar();
  resetLevels();
  delay(1000);
  
  
  Serial.println("Backward");
  for (int i = 50; i<200; i++) {
    speedLevel = i;
    driveBackward();
    delay(100);
  }
  stopCar();
  resetLevels();
  delay(1000);
  
  Serial.println("LEFT");
  speedLevel=80;
  turnLeftWithDrive();
  delay(4000);
  stopCar();
  resetLevels();
  delay(1000);

  Serial.println("RIGTH");
  speedLevel=80;
  turnRigthWithDrive();
  delay(4000);
  stopCar();
  resetLevels();
  delay(1000);
  
  delay(10000);
}

void stopCar() {
  digitalWrite(3, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);

  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  delay(50);
}

void resetLevels() {
  speedLevel = 0;
  digitalWrite(3, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);

  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(20);
}

void driveForward() {
  analogWrite(3, speedLevel);
  analogWrite(9, speedLevel);
  analogWrite(10, speedLevel);
  analogWrite(11, speedLevel);

  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);

  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void driveBackward() {
  analogWrite(3, speedLevel);
  analogWrite(9, speedLevel);
  analogWrite(10, speedLevel);
  analogWrite(11, speedLevel);

  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);

  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}


void turnLeftWithDrive() {
  
  speedLevel = speedLevel / 2;
  
  analogWrite(3, 123 - speedLevel);
  analogWrite(9, 123 + speedLevel);
  analogWrite(10, 123 - speedLevel);
  analogWrite(11, 123 + speedLevel);

  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);

  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  
}

void turnRigthWithDrive() {
  
  speedLevel = speedLevel / 2;
  
  analogWrite(3, 123 + speedLevel);
  analogWrite(9, 123 - speedLevel);
  analogWrite(10, 123 + speedLevel);
  analogWrite(11, 123 - speedLevel);

  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);

  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  
}
