/*
 * prog_lec_3_4_2_i2c0_master.ino: : 
 * PICO_DEFAULT_UART_BAUD_RATE 115200 
  
  Note: This needs to be built with the Raspberry Pi RP - Raspberry Pi Pico/RP2040

  HW connections: Connect this Tx board's pin 1 (GPIO 0, SDA0) to 
  pin 1 (GPIO 0, SDA0) of the Rx board
  and the Tx board's Pin no. 2 (GPIO 1, SCL0)to the 
  pin 2 (GPIO 1, SCL0) of the Rx board, note that I2C0 of both the boards 
  are used here to interface the Tx and Rx boards.
  Tx board receives the command from the user on Serial (USB) port and 
  passes it to the Rx board through I2C0. 
  We are using the Wire interface library provided by the
  RP2040 package to use the I2C devices on the boards.
  Caution: Though in this demo, only Tx board is sending data to Rx board,
  Rx is also capable of sending data back to Tx board on request.
  Always both SDA and SCL pins are to connected between Tx and Rx boards 
  Note: They should not be cross connected like in UART.
  
 Tx board blinks the built-in LED of other Rx board connected through I2C0.
 The program running on Rx board receives the commands from Tx board
 The commands that controls the blinking of built-in LED on Rx board.
 Commands: 'o' or 'O': ON, 'f' or 'F': OFF, 
 from 1 to 9 -> blink at 100 to 900 msecs

*/
// Wire is Arduino IDE's library for I2C peripheral in the board
// Wire relates to I2C0 device and Wire1 is I2C1 device on the board
// In this experiment both Tx and Rx boards use I2C0 device only.
#include <Wire.h>

bool LED_ON_flag = false;      // Default keep it blinking at default rate 1 sec

static int delayVal = 1000; // Default it is set to 1 second

#define CR_VAL 10
#define RX_BOARD_I2C_SLAVE1_ADDR 0x11

// The command coming in on Serial 0 from the serial monitor of this board
// to be sent on Serial 1 to the other board to control the built-in LED on the 
// other board
int incomingCMD = 0; 
int ledCMD = 0;       // It has the command from the other board to control this LED

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200); 

  // Mapping the GPIO for the I2C0 device
  Wire.setSDA(0);  // GPIO number 0 is mapped to the I2C0 SDA0 signal
  Wire.setSCL(1);  // GPIO number 1 is mapped to the I2C0 SCL0 signal
  // When Wire.begin is not given any device address because this I2C0 is 
  // configured as a Tx or Master device in the I2C network
  // After mapping I2C0 to the GPIO pins, enable I2C0
  Wire.begin();
  
  // Blink this LED based on the command from the other board
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH);
}

// the loop function runs over and over again forever
void loop() {

  static char cmdArr[1]; // One char array to be passed to Wire.transmission

  if(LED_ON_flag)
    digitalWrite(LED_BUILTIN, HIGH); // keep it always ON without any blinking
  else if (delayVal != 0){
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(delayVal);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delayVal);
  } else 
    digitalWrite(LED_BUILTIN, LOW); // keep it always OFF without any blinking

  char rx_char; // received through Serial USB port
  // Check if there is any command from the Serial Monitor sent by the user
  // Receive it and send it across to the other board through Serial 1
  if(Serial.available() > 0) {
    // read the incoming command byte:
    incomingCMD = Serial.read();

    // say what you got:
    Serial.print("Serial: Received the command: ");
    Serial.println(incomingCMD);
    // if it is not a carriage return then send it across to 
    // the other board through I2C0 
    if(incomingCMD != CR_VAL){
      cmdArr[0] = incomingCMD;
      // Send the command to the Slave Rx board 1
      Wire.beginTransmission(RX_BOARD_I2C_SLAVE1_ADDR);
      Wire.write(cmdArr, 1);   // length is only one char
      Wire.endTransmission();
      delay(100); // Small delay in case continuous chars are to be sent
    }  
  } // end of if Serial.available()
  
} // end of loop()