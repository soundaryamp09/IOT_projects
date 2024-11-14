const int trigPin = 12;
const int echoPin = 13;

const int R_LED = A0;
const int G_LED = A1;
const int Relay = A2;


int duration = 0;
int distance = 0;

void setup() 
{
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT);
  
  pinMode(R_LED , OUTPUT);
  pinMode(G_LED , OUTPUT);
  pinMode(Relay , OUTPUT);

  
  Serial.begin(9600);

}

void loop()
{
 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;

  if ( distance <= 4 )  // set value when you want to turn OFF water pump
  {
    digitalWrite(R_LED, HIGH);
    digitalWrite(G_LED, LOW);
    digitalWrite(Relay, LOW);
  }
  else if ( distance >= 7 )   // set value when you want to turn ON water pump
  {
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, HIGH);
    digitalWrite(Relay, HIGH);
  }
  
  delay(500);
}
