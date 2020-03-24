#include <ESP8266WiFi.h>

const char* ssid = "covid19";
const char* password = "gobloklu2";
WiFiServer server(80);
const int sleepSeconds = 5;

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);


  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val;
  if (req.indexOf("/msg?saywhat=matikan") != -1) {
    val = 0;
  }
  else if (req.indexOf("/msg?saywhat=nyalakan") != -1) {
    val = 1;
  }
  else if(req.indexOf("/msg/saywhat=disco") != 1){
    for (int i = 0; i < 100; i++)
  {
    digitalWrite(BUILTIN_LED, LOW);
    delay(100);
    digitalWrite(BUILTIN_LED, HIGH);
    delay(100);
  }
  Serial.println("Stop blinking");

  Serial.printf("Sleep for %d seconds\n\n", sleepSeconds);

  // convert to microseconds
  ESP.deepSleep(sleepSeconds * 1000000);
    }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  digitalWrite(2, val);

  client.flush();
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val) ? "high" : "low";
  s += "</html>\n";
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
}
