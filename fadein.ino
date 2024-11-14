void setup()
{
pinMode(11, OUTPUT);
}
void loop()
{
for (int i = 0; i <= 256; i++) {
analogWrite(11, i);
delay(20);
}}