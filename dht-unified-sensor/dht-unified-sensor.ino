// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example

// TEMPERATURE SENSORS - DHT11 (Digital Humidity Temperature)
/*
  3-5V operating voltage
  2.5mA max operating current
  0-50 deg temp range
  20-80% humidity range
  1Hz sampling range
  low cost but less accurate
*/
// DHT11 Sensor Library by Adafruit --> Install All

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7
#define DHTTYPE    DHT11     // DHT 11
// #define DHTTYPE    DHT22     // DHT 22 (AM2302)
// #define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHT11 Unified Sensor Example"));

  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  // Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  // Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  // Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  // Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  // Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  
  Serial.println(F("------------------------------------"));
  
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  // Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  // Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  // Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  // Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  // Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  // if(event.temperature >= 30) {
  //   Serial.println("HOT");
  //   digitalWrite(6, HIGH);
  //   digitalWrite(5, HIGH);
  // }
  // else if(event.temperature < 0) {
  //   Serial.println("COLD");
  //   digitalWrite(6, HIGH);
  //   digitalWrite(5, HIGH);
  // }
  // else {
  //   Serial.println("NORMAL");
  //   digitalWrite(6, LOW);
  //   digitalWrite(5, LOW);
  // }

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  if(event.relative_humidity >= 65) {
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
  }
  else if(event.relative_humidity < 0) {
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
  }
  else {
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
  }
}
