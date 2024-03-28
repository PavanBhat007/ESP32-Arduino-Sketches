#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

// WiFi Credentials
#define WIFI_SSID "Reno10"
#define WIFI_PASSWORD "24nithi24"

// SMTP Configuration
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "esp32snpn@gmail.com"
#define AUTHOR_PASSWORD "twnx etps zhbz bnnd"
#define RECIPIENT_EMAIL "nithyashree242003@gmail.com"
#include <SoftwareSerial.h>

String answ;

SoftwareSerial mySerial(11, 10);
// Sound Sensor and SD Card Pins
int senpin=A0;
const int ledPin = 42;    // Change as per your setup
const int soundPin = A0;  // Sound sensor pin
int threshold = 5000; // Threshold for noise detection
const int CS_PIN = 7;     // CS pin for the SD card module, change as per your setup


SMTPSession smtp;
Session_Config config;
SMTP_Message message;

File file;

void smtpCallback(SMTP_Status status) {
  if (status.success()) {
    Serial.println("Email sent successfully");
  } else {
    Serial.printf("Error sending Email, %s\n", status.info());
  }
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(soundPin, INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  if (!SD.begin(CS_PIN)) {
    Serial.println("Card Mount Failed");
    return;
  }
  Serial.println("SD Card initialized.");

  smtp.debug(1);
  smtp.callback(smtpCallback);

  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
}

void loop() {
  if(mySerial.available()!=0){
    answ=Serial.readStringUntil('\n');
    threshold=answ.toInt();
  }


  int soundLevel = analogRead(soundPin);
  Serial.println(soundLevel);
  delay(5000);
  mySerial.println(soundLevel);
  if (soundLevel >= threshold) {
    digitalWrite(ledPin, HIGH);
    logEvent("Noise Detected");
    sendEmail("Alert! Noise Detected");
    delay(10000); // Prevents multiple emails in a short time
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void logEvent(const char *event) {
  file = SD.open("/log.txt", FILE_APPEND);
  if (file) {
    String logEntry = getTimeStamp() + " - " + event;
    file.println(logEntry);
    file.close();
    Serial.println(logEntry);
  } else {
    Serial.println("Failed to open file for appending");
  }
}

String getTimeStamp() {
  // Get current time in milliseconds
  unsigned long currentTime = millis();

  // Convert milliseconds to seconds
  unsigned long seconds = currentTime / 1000;

  // Calculate hours, minutes, and seconds
  unsigned long hours = (seconds / 3600) % 24; // 24-hour format
  unsigned long minutes = (seconds % 3600) / 60;
  unsigned long secondsPart = seconds % 60;

  // Convert to a formatted timestamp
  char timestamp[20];
  sprintf(timestamp, "%02lu:%02lu:%02lu", hours, minutes, secondsPart);

  return String(timestamp);
}

void sendEmail(const char *messageBody) {
  SMTP_Message message;
  message.sender.name = "Your Name";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "ESP32 Noise Alert";
  message.addRecipient("Recipient Name", RECIPIENT_EMAIL);

  String textMsg = messageBody;
  message.text.content = textMsg.c_str();

  if (!smtp.connect(&config)) {
    Serial.println("SMTP Connection error");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message, true)) {
    Serial.println("Error sending Email");
  }
}