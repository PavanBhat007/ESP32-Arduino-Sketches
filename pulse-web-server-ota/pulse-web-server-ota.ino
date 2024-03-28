// SMART STETHOSCOPE

//                                    |-----> Web server
// Pulse sensor --> Arduino UNO --> ESP32 --> ThingSpeak channel
//                           |----> LCD I2C display

// ESP32 Code:
// Receive data from UNO via RX-TX (I2C)
// Publish data onto ThingSpeak
// Dispay results in web server


#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include "ThingSpeak.h"

#define LED 42
#define BUZZER 6
#define RELAY 5

#define SECRET_SSID "MotoGP"
#define SECRET_PASS "mourya203"

#define SECRET_CH_ID 2460963
#define SECRET_WRITE_APIKEY "IDSUC968GU39F142"
#define SECRET_READ_APIKEY "BDJMCECHQCAP3UXN"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "esp32snpn@gmail.com"
#define AUTHOR_PASSWORD "twnx etps zhbz bnnd"

#define RECIPIENT_EMAIL "padmashree0250@gmail.com"

unsigned long channelNumber = SECRET_CH_ID;
const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;
const char* writeAPIKey = SECRET_WRITE_APIKEY;
int keyIndex = 0;  

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

WiFiServer server(80);
WiFiClient client;

String header;

void smtpCallback(SMTP_Status status);
long measureSum = 0;

long vibration(){
  long measurement = pulseIn (vs, HIGH);
  return measurement;
}

void smtpCallback(SMTP_Status status){
  if (status.success()){
    Serial.println("Email sent successfully");
  }
}


void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(RELAY, LOW);
  
  // // Receiving data from Arduino UNO ---------------------------------------
  // Serial1.begin(9600, SERIAL_8N1, RX, TX);

  // Settign up WiFi & ThingSpeak ------------------------------------------
  WiFi.mode(WIFI_STA);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  long measurement = vibration();
  measureSum += measurement;

  int mea = measurement;
  int x = ThingSpeak.writeField(myChannelNumber, 1, measureSum, myWriteAPIKey);
  Serial.println(measurement);

  #include <WiFi.h>
#include <ESP_Mail_Client.h>
#include "ThingSpeak.h"

#define SECRET_CH_ID 2460963			// replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "IDSUC968GU39F142"

#define WIFI_SSID "MotoGP"
#define WIFI_PASSWORD "mourya203"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465 // Use 465 for SSL

#define AUTHOR_EMAIL "esp32snpn@gmail.com"
#define AUTHOR_PASSWORD "twnx etps zhbz bnnd"

#define RECIPIENT_EMAIL "padmashree0250@gmail.com"

#define led 42
#define BUZZER 6
#define vs 9

SMTPSession smtp;

char ssid[] = WIFI_SSID;   // your network SSID (name) 
char pass[] = WIFI_PASSWORD;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
int measurements [60];
int i = 0;

void smtpCallback(SMTP_Status status);
long measureSum = 0;

long vibration(){
  long measurement = pulseIn (vs, HIGH);
  return measurement;
}

void smtpCallback(SMTP_Status status){
  if (status.success()){
    Serial.println("Email sent successfully");
  }
}

void setup(){
  pinMode(led, OUTPUT);
  pinMode(vs, INPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(115200);
  Serial.print("Connecting to AP...");
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
}

void loop(){
  long measurement = vibration();
  measureSum += measurement;
  delay(50);
  int mea = measurement;
  int x = ThingSpeak.writeField(myChannelNumber, 1, measureSum, myWriteAPIKey);
  Serial.println(measurement);

  measurements[i] = measurement;
  i += 1;
  
  if (measureSum >= 1000){
    digitalWrite(led, HIGH);
    digitalWrite(BUZZER, HIGH);
    Serial.println("TREMOR Detected!");

    smtp.debug(1); // Enable debug messages
    smtp.callback(smtpCallback); // Set callback function

    // Configure SMTP session with your email credentials
    Session_Config config;
    config.server.host_name = SMTP_HOST;
    config.server.port = SMTP_PORT;
    config.login.email = AUTHOR_EMAIL;
    config.login.password = AUTHOR_PASSWORD;

    SMTP_Message message;
    message.sender.name = "TechnoFuturo";
    message.sender.email = AUTHOR_EMAIL;
    message.subject = "TREMOR!!!";
    message.addRecipient("Navani", RECIPIENT_EMAIL);

    // Email content
    String textMsg = "Alert! Tremor Detected";
    message.text.content = textMsg.c_str();

    // Connect and send email
    if (!smtp.connect(&config)) {
      Serial.println("Connection error");
      return;
    }

    if (!MailClient.sendMail(&smtp, &message, true)) {
      Serial.println("Error sending Email");
    }
  }
  else{
    digitalWrite(BUZZER, LOW);
    digitalWrite(led, LOW); 
  }


  // WiFi web-server
  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("NEW-CONNECTION");
    String currentLine = ""; 

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then => c -> response data
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"en\">");
            
            client.println("<head>");
            client.println("<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("<title>PULSIFY.ME</title>");
            client.println("<script src=\"https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js\"></script>");
            
            client.println("<style>");
            client.println("html {box-sizing: border-box;}");
            client.println("body {margin: 0;padding: 0;background-color: #222;color: whitesmoke;text-align: center;}");
            client.println(".heading, h3 {font-size: 60px;font-weight: 900;font-family: \"Franklin Gothic Medium\", \"Arial Narrow\", Arial, sans-serif;color: #ff3e5f;}");
            client.println(".heading, h3 {font-size: 60px;font-weight: 900;font-family: \"Franklin Gothic Medium\", \"Arial Narrow\", Arial, sans-serif;color: #ff3e5f;}");
            client.println("h3 {font-size: 30px;color: rgba(255, 225, 0, 0.5);font-weight: 400;}");
            client.println(".waves {margin-inline: auto;display: flex;justify-content: center;align-items: center;}");
            client.println("canvas {width: 100%;max-width: 800px;border: 1px solid rgba(255, 225, 0, 0.5);border-radius: 30px;}");
            client.println("</style></head>");
            
            client.println("<body>");
            client.println("<h1 class=\"heading\">❤️‍🔥PULSIFY.<i>ME</i></h1><h3>Average BPM: 72</h3><div class=\"waves\"><canvas id=\"chart\"></canvas></div>");
            
            client.println("<script>");
            client.print("const bpm = [");
            for(int j=0; j<i; j++) {
              client.print("'" + j + "',");
            }
            client.print("'" + i + "'];");
            client.println("const timestamp = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,];");
            client.println("new Chart(\"chart\", {");
            client.println("type: \"line\",data: {labels: timestamp,datasets: [{label:\"BPM (Beats Per Minute)\",backgroundColor: \"#ff3e5f\",borderColor: \"rgba(255,255,0,0.5)\",fill: true,data: bpm,borderWidth: 2,pointBackgroundColor: \"yellow\",pointHoverBackgroundColor: \"yellow\",point: {hitRadius: 1,},},],},");
            client.println("options: {scales: {xAxis: {title: {display: true,text: \"Time (Seconds)\",},},yAxis: {title: {display: true,text: \"Heart Rate (BPM)\",},},},},});");
            client.println("</script>");
            client.println("</body></html");
            client.println("");
            
            break;
          } else { 
            // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  
          // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
        }
      }
    }

    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

  // int x;
  // for(int i=0; i<10; i++) {
  //   x = ThingSpeak.writeField(channelNumber, 1, i, writeAPIKey);
  //   if(x == 200){
  //   Serial.println("Channel update successful.");
  //   }
  //   else{
  //     Serial.println("Problem updating channel. HTTP error code " + String(x));
  //   }
  //   delay(5000);
  // }


  // // Publishing to ThingSpeak channel --------------------------------------
  // int x;
  // x = ThingSpeak.writeField(channelNumber, 1, data, writeAPIKey);

  // if(x == 200){
  //   Serial.println("Channel update successful.");
  // }
  // else{
  //   Serial.println("Problem updating channel. HTTP error code " + String(x));
  // }
}