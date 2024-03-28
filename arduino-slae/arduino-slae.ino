// Arduino slave sketch
#include <Wire.h>

byte i2c_rcv;               // data received from I2C bus
unsigned long time_start;   // start time in mSec
byte PULSE;
int stat_LED;

void setup(){
	Wire.begin(0x08);           // join I2C bus as Slave with address 0x08
  Serial.begin(9600);
	
	// event handler initializations
	Wire.onReceive(dataRcv);    // register an event handler for received data
	Wire.onRequest(dataRqst);   // register an event handler for data requests
	
	// initialize global variables
	i2c_rcv = 255;
	time_start = millis();	
  stat_LED = 0;

	pinMode(42, OUTPUT);
}

void loop(){	
  // blink logic code
  if((millis() - time_start) > (1000 * (float)(i2c_rcv/255))) {
		stat_LED = !stat_LED;
		time_start = millis();
	}
	digitalWrite(42, stat_LED);
}

//received data handler function
void dataRcv(int numBytes){
	while(Wire.available()) {	
    // read all bytes received
		i2c_rcv = Wire.read();
    Serial.print(String(i2c_rcv));

	}
  Serial.println("");
}

// requests data handler function
void dataRqst(){
	Wire.write(PULSE); // send potentiometer position
}