/*
 * wifiSetup.h
 * 
 * Common helper file to contain a bunch of the common setup tasks that this device needs. 
 * This file is a required #include for all projects that use the MQTT/WiFi system. 
 * 
 */



//configure a webserver object for the configuration page (if required)
ESP8266WebServer configServer(80);
#define ssidAddr 0 //Locations in EEPROM memory where the SSID and Password will be stored. 
#define passAddr 64
#define IPAddr 256
#define deviceNameAddr 320
int serverStatus;

String clientName; //global to store the name of this device (based on the MAC, and the device name stored in the EEPROM)


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
  s += "<form method='get' action='a'>";
  s += "<label>SSID: </label><input name='ssid' length=32><label>Pass: </label><input name='pass' length=64><br/>";
    //This is a cheaty way to get the IP address, but I couldn't be bothered to get DNS lookups to work on the local network, so we'll have to assume that the MQTT broker remains on a static IP (which is valid whilst I control everything).
  s += "<label>IP: </label><input name='h1' length=4><input name='h2' length=4><input name='h3' length=4><input name='h4' length=4>";
  s += "<label>Device Name</label><input name='dn' length = 32>";
  s += "<input type='submit'></form>"; 
  s += "</html>\r\n\r\n";
  Serial.println("Sending 200");
  configServer.send(200, "text/html", s);
}


void handleSetup() {
  String ssid, pass, host1, host2, host3, host4, deviceName;
  ssid = configServer.arg("ssid");
  pass = configServer.arg("pass");
  host1 = configServer.arg("h1");
  host2 = configServer.arg("h2");
  host3 = configServer.arg("h3");
  host4 = configServer.arg("h4");
  deviceName = configServer.arg("dn");

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
  Serial.print("Device Name is: ");
  Serial.println(deviceName);

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
  EEPROM.write(IPAddr + 4, host2.toInt());
  EEPROM.write(IPAddr + 8, host3.toInt());
  EEPROM.write(IPAddr + 12, host4.toInt());
    for (int i = 0; i < pass.length() + 1; ++i) {
    EEPROM.write(deviceNameAddr + i, deviceName.c_str()[i]);
    Serial.print(deviceName.c_str()[i]);
  }
  Serial.println();
  EEPROM.commit();

  //  String s;
  //  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Configuration Complete. ";
  //  s+= "<p>Reboot the sensor (cycle power) to connect to the wifi network</p>";
  //   s += "</html>\r\n\r\n";
  //  Serial.println("Sending 200");
  //  configServer.send(200, "text/html", s);
  //
}

void startSoftAP() {

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(clientName.c_str()) ? "Ready" : "Failed!");  //clientName is generated in Setup and should be unique to the device since it's based on the MAC.
  Serial.println(WiFi.softAPIP());

  configServer.on("/", handleRoot);
  configServer.on("/a", handleSetup);
  configServer.begin();
  Serial.println("HTTP server started");
  serverStatus = 1; //Use this to decide whether to handle clients elsewhere in the sketch.
}

void connectToWiFi() {
  //Load WiFi data from the EEPROM, and useit to connect to the WiFi network.
  //This function is called whenever the code detects that it's not connected to Wifi.

  Serial.println("connectToWiFi() :");
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



  WiFi.hostname(clientName.c_str());  //Set the hostname of the wifi device so it appears names after the MAC on the setup page of routers etc.
  WiFi.begin(esid.c_str(), epass.c_str());
  int connectCount = 0;
  while ((WiFi.status() != WL_CONNECTED) && connectCount < 20) { //Should try to connect for ~30s
    delay(2000);
    Serial.print("*");
    connectCount ++;
  }
}

