int led = 13; 
int PinButton = 4; 
void setup() 
{ 
pinMode(PinButton, INPUT); 
pinMode(led, OUTPUT); 
} 
void loop() 
{ 
int stateButton = digitalRead(PinButton); 
if (stateButton == 1)
{ 
digitalWrite(led, HIGH); // Turn on led 
} 
else 
{ 
digitalWrite(led, LOW); //Turn off led 
} 
delay(20); 
}