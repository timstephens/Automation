
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
//#include <DHT.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ESP.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>


//configure a webserver object for the configuration page (if required)
ESP8266WebServer configServer(80);
#define ssidAddr 0 //Locations in EEPROM memory where the SSID and Password will be stored. 
#define passAddr 64
int serverStatus;

//DHT sens1(2, DHT11);

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
//IPAddress ip(192.168.0.9);
IPAddress server(192, 168, 0, 8);
//8*************



void handleRoot() {
  //Build a form to get the SSID and password for the network that we really want to join.
  // Read the first line of HTTP request
  String s;
  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
  s += WiFi.softAPIP();
  s += "<form method='get' action='a'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
  s += "</html>\r\n\r\n";
  Serial.println("Sending 200");
  configServer.send(200, "text/html", s);
}


void handleSetup() {
  String ssid, pass;
  ssid = configServer.arg("ssid");
  pass = configServer.arg("pass");

  Serial.print("SSID is ");
  Serial.println(ssid);
  Serial.print("Password is ");
  Serial.println(pass);

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
  serverStatus = 0; //This is the default case, where there is no server started for config.
  Serial.begin(115200);
  Serial.println("connected");

  EEPROM.begin(255); //Begin the EEPROM session

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

  WiFi.begin(esid.c_str(), epass.c_str());
  int connectCount = 0;
  while ((WiFi.status() != WL_CONNECTED) && connectCount < 20) { //Should try to connect for ~30s
    delay(500);
    Serial.print("*");
    connectCount ++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    //Need to serve up a page that offers the opportunity to enter server details etc.
    Serial.println("Failed to connect to WiFi netowrk.");
    Serial.println("Change to configuration mode");
    // Start the server
    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP("ESPsoftAP_012") ? "Ready" : "Failed!");
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

  //
  //  //Start the temperature sensor
  //    sens1.begin();

  sensors.begin();
}


void loop() {
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());

  if (serverStatus == 0) {
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
      ESP.deepSleep(300000000, WAKE_RF_DEFAULT);
    }
    client.loop();
  } else {
    configServer.handleClient();
  }
  //ESP.deepSleep(10000000,WAKE_RF_DEFAULT);
  //  }
}
