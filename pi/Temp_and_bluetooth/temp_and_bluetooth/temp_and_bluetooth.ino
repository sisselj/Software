

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

//temperatur sensor 
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 //Pin 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  bt.begin(9600);

  /* Since we run out of 5v PIN 
  * and don't wanna use a breadboard - the VCC of the DHT11
  * is connected to PIN 8
  * And we just use digitalWrite to put it HIGH
  */

}

void loop() {
  sensors.requestTemperatures();
  float T = get_Temp();
  //float hh = getHumid();
  //float tt = getTemp();
  //Serial.println(hh);
  //Serial.println(tt);
  bt.print (String(T));
  bt.print("\n");
  delay (1000); //prepare for data (2s)
}

float get_Temp() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  return (float)sensors.getTempCByIndex(0);
}


