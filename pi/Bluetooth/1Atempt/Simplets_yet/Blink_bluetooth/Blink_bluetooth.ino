#include <SoftwareSerial.h>    // For separate bluetooth serial data


// Bluetooth
SoftwareSerial bluetooth(6, 7); // Bluetooth RX, TX
const byte BTState = 8;         // Bluetooth STATE

const int pin = 2;
bool connected;

// Returns if connected or not
bool checkConnection(){
  return digitalRead(BTState) == HIGH;
}

void setup() {
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
}


void loop() {
   connected = checkConnection();


  if(connected){
  digitalWrite(pin, HIGH);
  Serial.println(1);
  delay(1000);              // wait for a second
  digitalWrite(pin, LOW);
  Serial.println(0);
  delay(1000);              // wait for a second
  }
}
