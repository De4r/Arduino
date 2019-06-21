#define SS_PIN 10
#define RST_PIN 9
#define LED_Y 3
#define LED_R 2
#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  Serial.println("Przyloz karte");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }

  Serial.print("UID tag: ");
  String content = "";
  

  for (byte i=0; i<mfrc522.uid.size;i++){
    Serial.print(mfrc522.uid.uidByte[i] <0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Wiadomosc : ");
  content.toUpperCase();
  if (content.substring(1) == "CB 7D 32 09") {
    Serial.println("Dostep");
    Serial.println();
    delay(250);
    digitalWrite(LED_Y, HIGH);
    delay(300);
    delay(500);
  } else if (content.substring(1) == "CB 7D 32 09"){
    Serial.println("Dostep");
    Serial.println();
    delay(250);
    digitalWrite(LED_Y, HIGH);
    digitalWrite(LED_R, HIGH);
    delay(300);
    delay(500);
  } else {
    Serial.println("Odmowa dostepu");
    analogWrite(LED_R, 30);
    delay(1000);
    digitalWrite(LED_R, LOW);
  }
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_R, LOW);
  delay(50);
}
