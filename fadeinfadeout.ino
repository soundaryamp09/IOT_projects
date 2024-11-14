#define LED_PIN 11
void setup()
{
pinMode(LED_PIN, OUTPUT);
}
void loop()
{
  // 255 means 5v then for 3v it is 153
for (int i = 0; i <= 255; i++) {
analogWrite(LED_PIN, i);
delay(10);
} 
for (int i = 255; i >= 0; i--) 
{
analogWrite(LED_PIN, i);
delay(10);
}}