#include "LedControl.h"
#include "font.h"
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>

const char* ssid = "virginmedia0465902";
const char* password = "mqqvrjww";
////MDNSResponder mdns;

String pl; //Somewhere to store the data forthe display? 
#define ARRAYCOLS 64
#define NUMARRAYS  4

// Parameters in LedControl are DIN, CLK, CS
//LedControl lc = LedControl(12, 11, 10, NUMARRAYS);// ARDUINO VERSION
LedControl lc = LedControl(14, 13, 12, NUMARRAYS); //ESP03  Version

/* we always wait a bit between updates of the display */
unsigned long delaytime = 500;


// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
//IPAddress ip(192.168.0.9);
IPAddress server(192,168,0,8);
//8*************
void callback(char* topic, byte* payload, unsigned int length) {
  pl =""; //This is a global string because Arduino. 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
   pl+=String((char)payload[i]);
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
      client.publish("/outTopic","hello world");
      // ... and resubscribe
      client.subscribe("/inTopic");
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
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  for (int devices = 0; devices < NUMARRAYS; devices++)
  {
    lc.shutdown(devices, false);

    /* Set the brightness to a medium values */
    lc.setIntensity(devices, NUMARRAYS);
    /* and clear the display */
    lc.clearDisplay(devices);
  }
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }//*/
   
    client.setServer(server, 1883);
  client.setCallback(callback);
}

void printChar(String row1Data) {

  /* ****************************************************
  Build up the text that you want to write to the screen
  into a buffer, made up of 64 chars (corresponding to a
  column each).
  Then write the buffer out to the display, reconfiguring
  it as appropriate for the display layout.
  **************************************************** */

  char buf[ARRAYCOLS];
  int c, i, count;
  int array, col;

  //Initialise the buffer so it's all zeros when we begin
  memset(buf, 0, sizeof(buf));

  count = 0; //counter for the current buffer position
  //String row1Data = "test";
  //For each character
  for (int index = 0; index < row1Data.length(); index++) {
    c = row1Data.charAt(index);
    for (int i = 0; i < 6; i++) { //For each column within a character
      buf[count] =  pgm_read_byte(&ASCII[(int)c][i]); //We're bit-shifting the data in one column at a time
      count++;
    }
  }
  //Once the buffer is full, write the data out to the LED array
  //There are 64 columns, so do a modulus%8 of the current index in the buffer. The mod is the array number and the remainder is the column.
  for (int i = 0; i < ARRAYCOLS; i++) {
    array = i / 8;
    col = 7 - (i % 8); //The column order is the reverse of the display order, so need to reverse it here by subtracting from 7.
    //i.e. col7 needs to be sent as col 1, etc.
    lc.setColumn(array, col, buf[i]);
  }
}


void loop() {

//  lc.setLed(3, i, i, true);
//  lc.setRow(2, 2, 0xFFFF);
//  lc.setColumn(1, 2, 0xFF);
//  lc.setLed(0, i, i, true);

  //printChar(String(millis(), DEC));
  printChar(pl);  //str(payload) should return a string from the payload, assuming that the payload is null terminated...

  delay(500);
  for (int devices = 0; devices < NUMARRAYS; devices++) {
    lc.clearDisplay(devices);
  }
  Serial.println("Main Loop");
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
