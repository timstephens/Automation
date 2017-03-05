
#include <WiFiClient.h>
//#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include "wifiSetup.h"




// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Update these with values suitable for your network.
IPAddress server(192, 168, 0, 8);  //Default, but is set on 'connect' from values stored in the EEPROM

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Handle control messages to this device

  if (strcmp(topic, "/control/heat") == 0) {
    if (payload[0] == '1') {
      Serial.println("Setting output high");
      digitalWrite(12, HIGH);
    } else {
      digitalWrite(12, LOW);
      Serial.println("Setting output low");
    }
  }
}

WiFiClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  //This connects to the MQTT broker
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientName.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("/control", clientName.c_str());
      // ... and resubscribe
      client.subscribe("/control/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }

    //The code gets trapped in this loop if the network settings are not correct, or if the broker IP is wrong. Provide an opportunity to escape to the settings server
    if (digitalRead(0) == 0) {
      startSoftAP();
    }
    if (serverStatus == 1) {
      configServer.handleClient();
    }
  }
}

//***************************


void setup() {

  EEPROM.begin(512); //Begin the EEPROM session

  int host1, host2, host3, host4; //the IP addresses of the mqtt broker.
  serverStatus = 0; //This is the default case, where there is no server started for config.
  Serial.begin(115200);
  Serial.println("connected");

  //Generate the MQTT clientname from the MAC Address.
  uint8_t mac[6];
  WiFi.macAddress(mac);

  //  String dn;
  //  for (int i = deviceNameAddr; i < 32; ++i)
  //  {
  //    dn += char(EEPROM.read(i));
  //  }

  clientName += "Switcher-";
  clientName += macToStr(mac);

  connectToWiFi();

  if (WiFi.status() != WL_CONNECTED) {
    //Need to serve up a page that offers the opportunity to enter server details etc.
    Serial.println("Failed to connect to WiFi netowrk.");
    Serial.println("Change to configuration mode");

    // Start the server
    startSoftAP();  //sets serverStatus = 1;



  } else {
    Serial.println("Connected to WiFi network ");
    //Serial.println(esid);
    client.setServer(server, 1883);
    client.setCallback(callback);
    //Stop the softAP if it's running, and disconnect all stations.
    //WiFi.softAPdisconnect(true);
  }
  //Setup the MQtt broker.
  host1 = EEPROM.read(IPAddr);  //Get the IP Address.
  host2 = EEPROM.read(IPAddr + 4);
  host3 = EEPROM.read(IPAddr + 8);
  host4 = EEPROM.read(IPAddr + 12);
  server = IPAddress(host1, host2, host3, host4);
  Serial.print("Broker IP=");
  Serial.println(server);
  //  //Start the temperature sensor

  sensors.begin();

  Serial.print("Number DS18b20 devices: ");
  Serial.println(sensors.getDeviceCount(), DEC);
  //setup some IO on various pins
  pinMode(12, OUTPUT);

}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  if (serverStatus == 0) {  //Only want to handle the webserver configuration stuff if it's running, so this handles the case if it's not.
    char buffer[10];
    sensors.requestTemperatures();
    // After we get the temperatures, we can print them here.
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    for (int i = 0; i < sensors.getDeviceCount(); i++) {
      Serial.print("Temperature for the device ");
      Serial.print(i, DEC);
      Serial.println(" is: ");
      Serial.println(sensors.getTempCByIndex(i));
      String tempC = String(sensors.getTempCByIndex(i));

      if (!client.connected()) {
        reconnect();
      } else {
        Serial.println("Publishing");
        String publishTopic = "/temperature/";
        publishTopic += clientName;
        publishTopic += "/";
        publishTopic += i; //Append the sensor number to the channel data
        client.publish(publishTopic.c_str(), (char *)tempC.c_str());
        delay(2000);

        //TODO: Fix this deepsleep bug
        //Serial.println("Done, Sleeping 10s");

        //ESP.deepSleep(10000000, WAKE_RF_DEFAULT);
      }
    }
    client.loop();

  } else {
    Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    configServer.handleClient();
  }
  if (digitalRead(0) == 0) {
    Serial.println("Prog pushed, running config server");
    startSoftAP();
  }
  delay(2000);
}
