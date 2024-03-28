int ir_sensor = 7; // obstacle detection
int ldr = 7; // light intensity

const int INBUILT_LED = 42;
const int BUZZER = 6;
const int RELAY = 5;

void setup() {
  // pinMode(ir_sensor, INPUT);
  pinMode(ldr, INPUT);
  pinMode(INBUILT_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // int data = digitalRead(ir_sensor);
  int data = digitalRead(ldr);
  Serial.println(data);

  if(data==1) {
    digitalWrite(BUZZER, HIGH);
  }
  else {
    digitalWrite(BUZZER, LOW);
  }
}
