// Wired Communication

// I2C: Inter Integrate Circuit
// popular for entertainment/infotainment systems

// UART : Universal Asynchronous Receiver and Transmitter
// TWI : Two Wire Interface

// Device 1 (SDA, SCL) connected to corresponding pins of Device 2 (SDA, SCL)
// SDA -> Serial Data
// SCL -> Serial Clock

// DATA TRANSFER
// | START BIT || ACK || ADDRESS (client) || ACK || DATA || ACK || DATA || ACK || STOP BIT | --> Serial Read

// //Write controller
// #include <Wire.h>

// void setup() {
//   Wire.begin(8);                // join i2c bus with address #8
//   Wire.onRequest(requestEvent); // register event
// }

// void loop() {
//   delay(100);
// }

// // function that executes whenever data is requested by master
// // this function is registered as an event, see setup()
// void requestEvent() {
//   Wire.write("D"); // respond with message of 6 bytes
//   // as expected by master
// }

//Read Controller
#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8,1);    // request 6 bytes from peripheral device #8

  // char* data;

  while (Wire.available()) { // peripheral may send less than requested
    int c = Wire.read();    // receive a byte as character
    Serial.println(c);
  }

  delay(500);
}

