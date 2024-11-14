int LEDpin = 13;   // LED pin  
	int PIRpin = 8;    // The pin of Arduino connected to the PIR output  
	int PIRvalue = 0;  // It specifies the status of PIR sensor  
	void setup() {  
	 pinMode(LEDpin, OUTPUT);       
	 pinMode(PIRpin, INPUT);  
 // the output from the sensor is considered as input for Arduino  
	 Serial.begin(9600);  
	}  
	void loop()  
	{  
	 PIRvalue = digitalRead(PIRpin);   
	 if (PIRvalue == HIGH)   
 {           
   digitalWrite(LEDpin, HIGH);    
	   // turn ON LED if the motion is detected  
	   Serial.println("hello, I found you...heyyy..");  
	 }   
 else   
	 {  
	   digitalWrite(LEDpin, LOW);  
	   // LED will turn OFF if we have no motion  
	   Serial.println("I cannot find you");  
   delay(1000);  
	 }  
   	}