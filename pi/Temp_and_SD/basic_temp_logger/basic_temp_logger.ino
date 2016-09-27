#include <SD.h>
#include <SPI.h>


#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int chip = 4; //SC to SC card.
File myData;

void setup() {
  Serial.begin(9600);
  sensors.begin();

  pinMode(10,OUTPUT);//this is strange
  SD.begin(chip);
}

void loop() {
  sensors.requestTemperatures();
  
  myData = SD.open("data.txt",FILE_WRITE);
  if (myData) {
    Serial.println(sensors.getTempCByIndex(0));
    myData.println(sensors.getTempCByIndex(0));
    myData.close();
    delay(1000);
  }
}
