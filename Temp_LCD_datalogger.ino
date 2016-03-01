/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(10, 9, 5, 8, 3, 7);

// SD card
const int chipSelect = 4;

void setup() {
  // start serial port
  Serial.begin(9600);
  //  Serial.println("Test...");
  
  SD.begin(chipSelect);
  // Start up the library
  sensors.begin();
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  
}

void loop() {
  
  // data for SD card
  String dataString = "";
  
  // open file 
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // set the cursor to column 0, line 1
  sensors.requestTemperatures(); // Send the command to get temperatures
  double temp = sensors.getTempCByIndex(0);
  Serial.println(temp);
  // (note: line 0 is the first row):
  lcd.setCursor(0, 0);
  //Printing temp
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("Time: ");
  int sekunder = (millis()/1000);
  int minutter = sekunder/60;
  int timer = minutter/60;
  
  if (minutter < 10){
    lcd.print(0);
  }
  
  lcd.print(minutter);
  lcd.print(":");
  
  
  if ((sekunder-(60*minutter)) < 10){
    lcd.print(0);
  }
  
  lcd.print(sekunder-(60*minutter));
  
  
  dataString += String(temp);
  // write data to file
  if (dataFile) {
    dataFile.print(millis()/1000.0);
    dataFile.print(", ");
    dataFile.println(dataString);
    dataFile.close();
  }
}



