/*
 Basic MQTT example

  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <ESP8266WiFi.h>
#include "PubSubClient.h"


const char* ssid = "virginmedia0465902";
const char* pass = "mqqvrjww";	//

// Update these with values suitable for your network.
IPAddress server(192, 168, 0, 8);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

WiFiClient wclient;
PubSubClient client(wclient);


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient12", "user", "pass")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  WiFi.mode(WIFI_STA);
  // Setup console
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  client.setServer(server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, pass);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    Serial.println("WiFi connected");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi conn 2");
    if (!client.connected()) {
      reconnect();
    }
     client.publish("outTopic", "hello world");

  }
 
  client.loop();
  Serial.println("Servicing Interrupts");
  delay(100);
}

