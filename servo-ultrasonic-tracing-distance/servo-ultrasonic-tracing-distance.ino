// #include <ESP32Servo.h>
// #include <Servo.h>

// Servo servo;
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(115200);
  // servo.attach(9);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  if(distance<5) {
    Serial.print("Distance: ");
    Serial.println(distance);
    // servo.write(distance);
    // delay(15);
  }
  else {
    Serial.println("Not in range(5cm)");
  }
  // delay(1000); //1s delay
}
