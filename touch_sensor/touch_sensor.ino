// TOUCH SENSOR - digital sensor
/*
  DTP223 IC
*/

const int TS = 7;
const int LED = 42;
int touch_count = 0;

void setup() {
  pinMode(TS, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  int touch_status = digitalRead(TS);
  Serial.println(touch_status);

  if(touch_status) {
    touch_count = touch_count+1;
  }

  if(touch_count%2 == 0) {
    digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(LED, HIGH);
  }
}
