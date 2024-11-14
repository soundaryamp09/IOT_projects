int sensorPin = 2;
volatile long pulse;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(112500);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
}

void loop() {
  Serial.print(pulse);
  delay(500);
}
void increase() {
  pulse++;
}