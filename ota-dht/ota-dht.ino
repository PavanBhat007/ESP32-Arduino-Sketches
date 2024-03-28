// OTA - Over The Air: upload code to board over IP
// board running on some IP address and using that we
// can upload the code while board is not connected to laptop via UART cable

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <DHT_U.h>

// #define DHTPIN 7
// #define DHTTYPE    DHT11     // DHT 11

// DHT_Unified dht(DHTPIN, DHTTYPE);
// uint32_t delayMS;

const char* ssid = "SSID";
const char* password = "1357986420";

void setup() {  
  pinMode(42, OUTPUT);
  // Initialize device.
  // dht.begin();
  // Serial.println(F("DHT11 Unified Sensor Example"));
  
  // // Print temperature sensor details.
  // sensor_t sensor;

  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  // ArduinoOTA.setHostname("myesp32");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.print
  
  ln("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // delayMS = sensor.min_delay / 1000;
}

void loop() {
  // delay(delayMS);
  ArduinoOTA.handle();

  // sensors_event_t event;
  // dht.temperature().getEvent(&event);
  // if (isnan(event.temperature)) {
  //   Serial.println(F("Error reading temperature!"));
  // }
  // else {
  //   Serial.print(F("Temperature: "));
  //   Serial.print(event.temperature);
  //   Serial.println(F("°C"));
  // }

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
}