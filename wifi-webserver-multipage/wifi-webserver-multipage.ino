#include <WiFi.h>

#define PAGE_HOME 0
#define PAGE_TEMPERATURE 1
#define PAGE_DOOR 2
#define PAGE_LED 3

#define PAGE_ERROR_404 -1
#define PAGE_ERROR_405 -2

const char ssid[] = "SSID";  // change your network SSID (name)
const char pass[] = "1357986420";   // change your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    // read the first line of HTTP request header
    String HTTP_req = "";
    while (client.connected()) {
      if (client.available()) {
        Serial.println("New HTTP Request");
        HTTP_req = client.readStringUntil('\n');  // read the first line of HTTP request
        Serial.print("<< ");
        Serial.println(HTTP_req);  // print HTTP request to Serial Monitor
        break;
      }
    }

    // read the remaining lines of HTTP request header
    while (client.connected()) {
      if (client.available()) {
        String HTTP_header = client.readStringUntil('\n');  // read the header line of HTTP request

        if (HTTP_header.equals("\r"))  // the end of HTTP request
          break;

        //Serial.print("<< ");
        //Serial.println(HTTP_header);  // print HTTP request to Serial Monitor
      }
    }

    // ROUTING
    // This example supports the following:
    // - GET /
    // - GET /index
    // - GET /index.html
    // - GET /temperature
    // - GET /temperature.html
    // - GET /door
    // - GET /door.html
    // - GET /led
    // - GET /led.html

    int page_id = 0;

    if (HTTP_req.indexOf("GET") == 0) {  // check if request method is GET
      if (HTTP_req.indexOf("GET / ") > -1 || HTTP_req.indexOf("GET /index ") > -1 || HTTP_req.indexOf("GET /index.html ") > -1) {
        Serial.println("home page");
        page_id = PAGE_HOME;
      } else if (HTTP_req.indexOf("GET /temperature ") > -1 || HTTP_req.indexOf("GET /temperature.html ") > -1) {
        Serial.println("temperature page");
        page_id = PAGE_TEMPERATURE;
      } else if (HTTP_req.indexOf("GET /door ") > -1 || HTTP_req.indexOf("GET /door.html ") > -1) {
        Serial.println("door page");
        page_id = PAGE_DOOR;
      } else if (HTTP_req.indexOf("GET /led ") > -1 || HTTP_req.indexOf("GET /led.html ") > -1) {
        Serial.println("led page");
        page_id = PAGE_LED;
      } else {  // 404 Not Found
        Serial.println("404 Not Found");
        page_id = PAGE_ERROR_404;
      }
    } else {  // 405 Method Not Allowed
      Serial.println("405 Method Not Allowed");
      page_id = PAGE_ERROR_405;
    }

    // send the HTTP response
    // send the HTTP response header
    if (page_id == PAGE_ERROR_404)
      client.println("HTTP/1.1 404 Not Found");
    if (page_id == PAGE_ERROR_405)
      client.println("HTTP/1.1 405 Method Not Allowed");
    else
      client.println("HTTP/1.1 200 OK");

    client.println("Content-Type: text/html");
    client.println("Connection: close");  // the connection will be closed after completion of the response
    client.println();                     // the separator between HTTP header and body

    // send the simple HTTP response body
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    client.println("</head>");

    String html;
    switch (page_id) {
      case PAGE_HOME:
        client.println("This is home page");
        break;
      case PAGE_TEMPERATURE:
        client.println("This is temperature page");
        break;
      case PAGE_DOOR:
        client.println("This is door page");
        break;
      case PAGE_LED:
        client.println("This is LED page");
        break;
      case PAGE_ERROR_404:
        client.println("Page Not Found");
        break;
      case PAGE_ERROR_405:
        client.println("Method Not Allowed");
        break;
    }

    client.println("</html>");
    client.flush();

    client.flush();

    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
  }
}

void printWifiStatus() {
  // print your board's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // print the received signal strength:
  Serial.print("signal strength (RSSI):");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}
