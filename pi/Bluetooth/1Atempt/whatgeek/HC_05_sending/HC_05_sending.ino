//This sketch shows how to connect to a bluetooth device
// Arduino -> bluetooth
// Used with Android BlueTerm app

#include <SoftwareSerial.h> //Serial library

/**
 * Arduino connection HC-05 connection: 
 * HC-05  | Arduino
 * TX     | 5
 * RX     | 6
*/
// Here, we exchange them -
SoftwareSerial bt (5,6);  //RX, TX (Switched on the Bluetooth - RX -> TX | TX -> RX)
int LEDPin = 13; //LED PIN on Arduino
int btdata; // the data given from the computer

void setup() {
  bt.begin(9600); //Open the serial port
  bt.println ("Bluetooth ON. Press 1 or 0 to blink LED.."); //write to serial
  pinMode (LEDPin, OUTPUT);
}

void loop() {
  if (bt.available()) { //if serial is available
    btdata = bt.read(); //read from the serial connection
    if (btdata == '1') {
      //if 1
      digitalWrite (LEDPin, HIGH); //if we get 1, turn on the LED
      bt.println ("LED ON!");
    }
    if (btdata == '0') { //if we received 0, turn off the led
      //if 0
      digitalWrite (LEDPin, LOW);
      bt.println ("LED OFF!");
    }
  }
  delay (100); //prepare for data
}
