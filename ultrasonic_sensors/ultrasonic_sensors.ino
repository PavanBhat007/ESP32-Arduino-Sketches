// based on crystal oscillator
/* 
  spd of sound = 340 m/s = 0.034 m/microseconds
  time = 10/spd = 10/0.034 = 294.11 microseconds
  dist = (spd*time)/2
*/

const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin (9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH); //inbuilt timings => clock
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000); //1s delay
}
