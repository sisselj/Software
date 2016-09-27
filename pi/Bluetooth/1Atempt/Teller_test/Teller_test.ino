
int teller = 0;

void setup(){
  Serial.begin(9600);
  delay(50);
}

void loop(){
  teller ++;
  Serial.print("Arduino teller:");
  Serial.print(teller);
  delay(500);
}

