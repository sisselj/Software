// --- Dependencies ---
#include <SoftwareSerial.h>    // For separate bluetooth serial data
#include <LiquidCrystal_I2C.h> // For LCD over I2C
#include <OneWire.h>           // For Dallas over OneWire
#include <DallasTemperature.h> // For Dallas

// --- Pins ---
// Bluetooth
SoftwareSerial bluetooth(6, 7); // Bluetooth RX, TX
const byte BTState = 8;         // Bluetooth STATE
// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C address is 0x27, 16x2 chars
// Dallas sensor
const byte oneWireBus = 2;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// --- Variables ---
bool connected;
// Data structure to send
struct __attribute__ ((packed)) packet { // Ensure the structure is not padded
  unsigned long timeElapsed;             // Time stamp
  float temperature;                     // Temperature
} data;

// --- Cgonstants ---
const unsigned long updateFrequency = 1000;

// --- Functions ---
// Writes data packet to bluetooth serial
void writeStruct(packet data) {
  bluetooth.write((byte*) &data, sizeof(packet));
  Serial.print("time: ");
  Serial.print(data.timeElapsed);
  Serial.print(", temp: ");
  Serial.println(data.temperature);
}
// Returns temperature
float getTemperature(int i){
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(i);
}
// Returns if connected or not
bool checkConnection(){
  return digitalRead(BTState) == HIGH;
}
// Updates the LCD
void updateLcd(packet data, bool connected){
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("T=");
  lcd.print(data.temperature, 1);
  lcd.print("C");

  lcd.setCursor(8,0);
  lcd.print("t=");
  lcd.print(data.timeElapsed/1000., 0);
  lcd.print("s");

  lcd.setCursor(0,1);
  if(connected){
    lcd.print("Connected!");
  }else{
    lcd.print("No connection...");
  }
}

void setup() {
  pinMode(BTState, INPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  data.timeElapsed = millis();
  data.temperature = getTemperature(0);
  connected = checkConnection();

  updateLcd(data, connected);
  if(connected){
    writeStruct(data);
  }

  delay(updateFrequency);
}
