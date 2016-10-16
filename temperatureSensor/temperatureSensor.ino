
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
//#include <DHT.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP.h>



//DHT sens1(2, DHT11);

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "virginmedia0465902";
const char* password = "mqqvrjww";
////MDNSResponder mdns;



// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
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
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("/control", "WeatherBug!");
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
//    sens1.begin();

  sensors.begin();
}


void loop() {

  char buffer[10];
//  float t1, h1;
//    t1 = 4.56; //sens1.readTemperature();
//    h1 = 5.46; //sens1.readHumidity();
//    String tempF = String(t1, DEC); //dtostrf(t1, 4, 1, buffer); //
//    tempF += " ";
//    tempF  += String(h1, DEC); //dtostrf(h1, 4, 1, buffer); //
// 
  //  for (int myloop = 0; myloop < 5; myloop++) {
  sensors.requestTemperatures();
   // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));  
  delay(2000);
  String tempC = String(sensors.getTempCByIndex(0));

  Serial.println("Main Loop");
  if (!client.connected()) {
    reconnect();
  } else {
    client.publish("/outTemp", (char *)tempC.c_str());
    Serial.println("Sleeping 300s");
    ESP.deepSleep(300000000,WAKE_RF_DEFAULT); 
  }
  client.loop();

  //ESP.deepSleep(10000000,WAKE_RF_DEFAULT); 
  //  }
}
