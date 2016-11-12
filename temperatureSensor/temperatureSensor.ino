
#include <WiFiClient.h>
//#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>


//configure a webserver object for the configuration page (if required)
ESP8266WebServer configServer(80);
#define ssidAddr 0 //Locations in EEPROM memory where the SSID and Password will be stored. 
#define passAddr 64
#define IPAddr 256
int serverStatus;



// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Update these with values suitable for your network.

IPAddress server(192, 168, 0, 8);  //Default
String clientName; //global to store the name of this device (based on the MAC)

//8*************

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}


void handleRoot() {
  //Build a form to get the SSID and password for the network that we really want to join.
  // Read the first line of HTTP request
  String s;
  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
  s += WiFi.softAPIP();
  s += "<form method='get' action='a'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><br/><input name='host1' length=4><input name='host2' length=4><input name='host3' length=4><input name='host4' length=4><input type='submit'></form>";  //This is a cheaty way to get the IP address, but I couldn't be bothered to get DNS lookups to work on the local network, so we'll have to assume that the MQTT broker remains on a static IP (which is valid whilst I control everything).
  s += "</html>\r\n\r\n";
  Serial.println("Sending 200");
  configServer.send(200, "text/html", s);
}


void handleSetup() {
  String ssid, pass, host1, host2, host3, host4;
  ssid = configServer.arg("ssid");
  pass = configServer.arg("pass");
  host1 = configServer.arg("host1");
  host2 = configServer.arg("host2");
  host3 = configServer.arg("host3");
  host4 = configServer.arg("host4");

  Serial.print("SSID is ");
  Serial.println(ssid);
  Serial.print("Password is ");
  Serial.println(pass);
  Serial.print("Conecting to ");
  Serial.print(host1);
  Serial.print(".");
  Serial.print(host2);
  Serial.print(".");
  Serial.print(host3);
  Serial.print(".");
  Serial.println(host4);

  // IPAddress host(host1.toInt(), host2().toInt, host3.toInt(), host4.toInt());
  //Now need to set the SSID and password into the memory of the ESP, and make it reconnect to that.
  //There also needs to be some though about how we make it try to connect to the wifi first.
  for (int i = 0; i < ssid.length() + 1; ++i) {
    EEPROM.write(ssidAddr + i, ssid.c_str()[i]);
    Serial.print(ssid.c_str()[i]);
  }
  Serial.println();
  for (int i = 0; i < pass.length() + 1; ++i) {
    EEPROM.write(passAddr + i, pass.c_str()[i]);
    Serial.print(pass.c_str()[i]);
  }
  EEPROM.write(IPAddr, host1.toInt());
  EEPROM.write(IPAddr+4, host2.toInt());
  EEPROM.write(IPAddr+8, host3.toInt());
  EEPROM.write(IPAddr+12, host4.toInt());
  Serial.println();
  EEPROM.commit();
}

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
    if (client.connect(clientName.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("/control", clientName.c_str());
      // ... and resubscribe
      client.subscribe("/control");
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
  int host1, host2, host3, host4; //the IP addresses of the mqtt broker.
  serverStatus = 0; //This is the default case, where there is no server started for config.
  Serial.begin(115200);
  Serial.println("connected");

  //Generate the MQTT clientname from the MAC Address.
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += "TempSensor-";
  clientName += macToStr(mac);

  EEPROM.begin(512); //Begin the EEPROM session

  Serial.println("Values stored in EEPROM are:");
  Serial.println("Reading EEPROM ssid");
  String esid;
  for (int i = ssidAddr; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  String epass = "";
  for (int i = passAddr; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);

  host1 = EEPROM.read(IPAddr);  //Get the IP Address. 
  host2 = EEPROM.read(IPAddr + 4);
  host3 = EEPROM.read(IPAddr + 8);
  host4 = EEPROM.read(IPAddr + 12);

  server = IPAddress(host1, host2, host3, host4);
  Serial.print("Broker IP=");
  Serial.println(server);
  WiFi.hostname(clientName.c_str());  //Set the hostname of the wifi device so it appears names after the MAC on the setup page of routers etc.
  WiFi.begin(esid.c_str(), epass.c_str());
  int connectCount = 0;
  while ((WiFi.status() != WL_CONNECTED) && connectCount < 20) { //Should try to connect for ~30s
    delay(2000);
    Serial.print("*");
    connectCount ++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    //Need to serve up a page that offers the opportunity to enter server details etc.
    Serial.println("Failed to connect to WiFi netowrk.");
    Serial.println("Change to configuration mode");

    // Start the server

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(clientName.c_str()) ? "Ready" : "Failed!");  //clientName is generated in Setup and should be unique to the device since it's based on the MAC.
    Serial.println(WiFi.softAPIP());

    configServer.on("/", handleRoot);
    configServer.on("/a", handleSetup);
    configServer.begin();
    Serial.println("HTTP server started");
    serverStatus = 1; //Use this to decide whether to handle clients elsewhere in the sketch.


  } else {
    Serial.print("Connected to WiFi network ");
    Serial.println(esid);
    client.setServer(server, 1883);
    client.setCallback(callback);
  }
  //

  //  //Start the temperature sensor

  sensors.begin();
}


void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());

  if (serverStatus == 0) {  //Only want to handle the webserver stuff if it's running.
    char buffer[10];
    sensors.requestTemperatures();
    // After we get the temperatures, we can print them here.
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(sensors.getTempCByIndex(0));
    String tempC = String(sensors.getTempCByIndex(0));

    if (!client.connected()) {
      reconnect();
    } else {
      Serial.println("Publishing");
      String publishTopic = "/temperature/";
      publishTopic += clientName; 
      client.publish(publishTopic.c_str(), (char *)tempC.c_str());
      delay(2000);
      Serial.println("Done, Sleeping 300s");
      ESP.deepSleep(300000000, WAKE_RF_DEFAULT);
    }
    client.loop();
    
  } else {
    configServer.handleClient();
  }
  delay(2000);
}
