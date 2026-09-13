const int fanPin = 9;

void setup() {
  pinMode(fanPin, OUTPUT);
}

void loop() {
  analogWrite(fanPin, 255);
  delay(3000);

  analogWrite(fanPin, 0);
  delay(3000);
}
