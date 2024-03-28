const int LED = 42;
const int PM = 7;

void setup() {
  pinMode(PM, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  int data = analogRead(PM); //read analogous values
  // Serial.println(data);
  analogWrite(LED, data); //write analogous values
}
