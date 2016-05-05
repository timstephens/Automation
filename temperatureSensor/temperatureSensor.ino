
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(2); //Set up on GPIO2

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


const char* ssid = "wifi";
const char* password = "hunter77";
////MDNSResponder mdns;



// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };
//IPAddress ip(192.168.0.9);
IPAddress server(192, 168, 0, 8);
//8*************
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

WiFiClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClien")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("/outTemp", "WeatherBug!");
      // ... and resubscribe
      client.subscribe("/inWeather");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//***************************



void setup() {
  Serial.begin(115200);
  Serial.println("connected");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }//*/
  //
  client.setServer(server, 1883);
  client.setCallback(callback);
  //
  //  //Start the temperature sensor
 sensors.begin();
}


void loop() {

  char buffer[10];
  float t1;

  sensors.requestTemperatures(); // Send the command to get temperatures
    
   
    String tempF = String(sensors.getTempCByIndex(0), DEC); //dtostrf(t1, 4, 1, buffer); //
 
  //  for (int myloop = 0; myloop < 5; myloop++) {
  delay(2000);


  Serial.println("Main Loop");
  if (!client.connected()) {
    reconnect();
  } else {
    client.publish("/outTemp", (char *)tempF.c_str());

  }
  client.loop();
  //  }
}
