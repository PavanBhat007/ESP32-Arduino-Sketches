/*
  SERVO MOTOR - AC
  cant control angle of shaft spin || no specific stop position || +ve, -ve pins
  servomotor has built-in features to adjust angle of shaft || specific shaft position exists || +ve, -ve and signal pins
  0 to 180 degrees only

  PWN -> Pulse Width Modulation
  Applications: robotics, smart locks
*/

#include <ESP32Servo.h>

Servo servo;
int pos = 0;

void setup() {
  Serial.begin(115200); //changing modrate
  servo.attach(9); //pin where motor will be attached
}

void loop() {
  for(pos=0; pos<=180; pos++) {
    servo.write(pos); //servo rotation
    delay(15);
  }
  for(pos=180; pos>=0; pos--) {
    servo.write(pos); //servo rotation
    delay(15);
  }
}
