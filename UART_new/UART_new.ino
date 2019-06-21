int liczba = 2345;
float liczbaPI = 3.1415;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(liczba);
  Serial.println(liczba, DEC);
  Serial.println(liczba, HEX);
  Serial.println(liczba, OCT);
  Serial.println(liczba, BIN);
  Serial.println(liczbaPI, 4);
  Serial.println(liczbaPI, 0);

  Serial.println(PI);
  Serial.print("witaj");
  Serial.print(". Dalej w tej samej lini \n A teraz juz nie");
}

void loop() {
  // put your main code here, to run repeatedly:

}
