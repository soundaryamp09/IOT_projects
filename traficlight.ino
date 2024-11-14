#define LED_PIN_1 11
#define LED_PIN_2 10
#define LED_PIN_3 9
void setup()
{
pinMode(LED_PIN_1, OUTPUT);
pinMode(LED_PIN_2, OUTPUT);
pinMode(LED_PIN_3, OUTPUT);
}
void loop()
{
digitalWrite(LED_PIN_1, HIGH);
digitalWrite(LED_PIN_2, LOW);
digitalWrite(LED_PIN_3, LOW);
delay(3000);
digitalWrite(LED_PIN_1, LOW);
digitalWrite(LED_PIN_2, HIGH);
digitalWrite(LED_PIN_3, LOW);
delay(2000);
digitalWrite(LED_PIN_1, LOW);
digitalWrite(LED_PIN_2, LOW);
digitalWrite(LED_PIN_3, HIGH);
 delay(1000); 
 }