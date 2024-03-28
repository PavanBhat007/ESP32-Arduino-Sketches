#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  Wire.begin(21, 22); //SDA, SCL
  //--------------

}

void loop()
{
  Wire.beginTransmission(0x23);
  byte busStatus = Wire.endTransmission();
  if (busStatus != 0)
  {
    Serial.print("UNO is not found!");
    while (1); //wait for ever
  }
  Serial.println("UNO is found.");
  delay(1000);
}