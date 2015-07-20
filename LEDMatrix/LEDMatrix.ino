#include "LedControl.h"
#include "font.h"
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <String.h>


const char* ssid = "virginmedia0465902";
const char* password = "mqqvrjww";
//MDNSResponder mdns;
IPAddress server(192, 168, 0, 8);


#define ARRAYCOLS 128
#define NUMARRAYS  8


//Define the pins that are needed to talk to the LED array
LedControl lc = LedControl(14, 13, 12, NUMARRAYS); //12, 11, 10, NUMARRAYS);
//Create a wifiClient.
WiFiClient wifiClient;


/* we always wait a bit between updates of the display */
unsigned long delaytime = 500;



void callback(const MQTT::Publish& pub) {
  // handle message arrived
  Serial.println("Callback");
}


PubSubClient pubsub(wifiClient, server, 1883);  //Explicitly mention the port that we connect to.

void clearDisplays() {
  for (int devices = 0; devices < NUMARRAYS; devices++) {
    lc.clearDisplay(devices);
  }
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
    lc.setIntensity(devices, 8);
    /* and clear the display */
    lc.clearDisplay(devices);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  pubsub.set_callback(callback);
}



void loop() {

  //lc.setLed(3, i, i, true);
  //  lc.setRow(2, 2, 0xFFFF);
  //lc.setColumn(1, 2, 0xFF);
  //lc.setLed(0, i, i, true);

  printChar(String(millis(), DEC));

  delay(500);

  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.println("Main Loop");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wifi connected");
    if (!pubsub.connected()) {
      if (pubsub.connect("arduinopubsub")) {
        Serial.println("Connected to MQTT broker");
        pubsub.publish("/test", "hello world");
        pubsub.subscribe("/inTopic");
      } else {
        Serial.println("Think I am connected to the broker...");
         pubsub.publish("/test", "hello world2");
      }
    }

    if (pubsub.connected())
      pubsub.loop(); //*/
  }

  clearDisplays();

}
