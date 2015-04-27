/*
 *  TJS 25th April 2015
 *
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdlib.h>
#include <ESP.h>

const char* ssid     = "virginmedia0465902";
const char* password = "mqqvrjww";
const char* host = "192.168.0.105";

byte server[] = {192, 168, 0, 105}; //Different format from the example this is based on.

int value = 0;

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);
OneWire ds(2);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&ds);



void setup() {
  Serial.begin(115200);
  delay(10);
  sensors.begin();


  // We start by connecting to a WiFi network

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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect("arduinoClient", "username", "passowrd")) {
    Serial.println("Client Connected");
    client.publish("/status","Connected");
  } else {
    Serial.println("Failed to connect");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Callback Fired");
}




void loop() {
  float temp;
  delay(10000);
  ++value;
  //read temperature value in here...
  Serial.print("connecting to ");
  Serial.println(host);
   sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.print("Temperature for the device 1 (index 0) is: ");
  temp = sensors.getTempCByIndex(0);
  Serial.println(temp); 


 if(client.connected()){
    Serial.println("Connected");
    String temperature = "temp:";
    temperature += temp;
    
    client.publish("/temperature", (char*)temperature.c_str());
    client.subscribe("/inTopic");
  } else {
    Serial.println("Not connected");
  }

  Serial.println("Publishing complete");
  client.loop(); //Allow the client to service inputs from the server and remain connected.  
  ESP.deepSleep(1000000, WAKE_RF_DEFAULT); //Should Cause the board to sleep for 10s.
  


}

