/*
 * prog_lec_3_4_2_i2c0_slave.ino: : 
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
#include <Wire.h>

void control_LED(uint32_t ledCmd);
bool LED_ON_flag = false;   // Default keep it blinking at default rate 1 sec

static int delayVal = 1000; // Default it is set to 1 second

#define CR_VAL 10
#define RX_BOARD_I2C_SLAVE1_ADDR 0x11

// The command coming in on Serial 0 from the serial monitor of this board
// to be sent on Serial 1 to the other board to control the built-in LED on the 
// other board
uint32_t ledCMD = 0;       // It has the command from the other board to control this LED
static volatile char rxCMD = 0;

// Called when the I2C slave gets written to by the master (Tx board)
void recvCMD(int len) {
    int i;
    char rxVal;
    for (i=0; i<len; i++) {
      rxVal = Wire.read();
      if(rxVal != 0xFF)
        rxCMD = rxVal;
    }
} // end of recvCMD(int len)

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);    
  Wire.setSDA(0);  // GPIO number 0 is mapped to the I2C0 SDA0 signal
  Wire.setSCL(1);  // GPIO number 1 is mapped to the I2C0 SCL0 signal
  // When Wire.begin is passed the device address this I2C0 is 
  // configured as a Slave device in the I2C network with that address
  // After mapping I2C0 to the GPIO pins, enable I2C0
  Wire.begin(RX_BOARD_I2C_SLAVE1_ADDR);
  // The fn to execute when the slave receives command from Tx board  
  Wire.onReceive(recvCMD);  
  
  // Blink this LED based on the command from the other board
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH);
}

// the loop function runs over and over again forever
void loop() {
  if(LED_ON_flag)
    digitalWrite(LED_BUILTIN, HIGH); // keep it always ON without any blinking
  else if (delayVal != 0){
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(delayVal);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delayVal);
  } else 
    digitalWrite(LED_BUILTIN, LOW); // keep it always OFF without any blinking

  //Serial.print("delayVal = ");
  //Serial.println(delayVal);
  
  // Check if there is any command on the I2C 0 from the other board
  // Receive it and control the built-in LED of this board
  // This the command given by the user on the Serial monitor of the other board
  if(rxCMD) {
      ledCMD = (uint32_t) rxCMD;
      rxCMD = 0;
      // say what you got:
      Serial.print("I2C0: Received the LED command: ");
      Serial.println(ledCMD, HEX);
      control_LED(ledCMD);
  } // if rxCMD received from Tx board
  
} // end of loop()

// Valid single byte commands to control the built-in LED:
// o or O: All LEDs ON
// f or F: All LEDs OFF
// 1 to 9: Blink the LED at 100 to 900 milliseconds

void control_LED(uint32_t ledCmd){
  
  switch(ledCmd){
    case 'o':   // Always ON
    case 'O':
      LED_ON_flag = true;
      delayVal = 0;
      break;
    case 'f':   // Always OFF
    case 'F':
      LED_ON_flag = false;
      delayVal = 0;
      break;          
     // If the command is between 1 and 9 change delayVal accordinlgy
     // Any other data received then ignore it and no action taken 
    default:
      Serial.println("control_LED: Default case");
      LED_ON_flag = false;
      if(ledCmd >= '1' && ledCmd <= '9'){
        Serial.println(ledCmd);
        delayVal = (ledCmd - '0') * 100; // in milliseconds
      }
      break;
      
  } // end of switch
  
} // end of control_LMD(int ledCmd)