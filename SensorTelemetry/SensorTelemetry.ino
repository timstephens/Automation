#include <SPI.h>
#include <RF24.h>
#include "DHT.h"
#include "printf.h"

// ce,csn pins
RF24 radio(9,10);


//Temp Sensors
DHT dht(2, DHT22);
//DHT sens2(3, DHT11);


void setup(void)
{
  // init radio for writing on channel 76
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x4c);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();
//*/
  dht.begin();

  Serial.begin(9600);
  //while(!Serial);
  Serial.println("Initialised");
  printf_begin();
  radio.printDetails();
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
}

void loop(void)
{
  // 32 bytes is maximum payload
  String outputString;
  char outBuffer[32]= "";
  char floatBuf1[10];
  char floatBuf2[10];
  float h, t;
  Serial.print("Reading Data...");
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.println("Done");

  //dtostrf(h, 6, 2, floatBuf1);
  //dtostrf(t, 6, 2, floatBuf2);
  // pad numbers and convert to string
  //sprintf(outBuffer,"S1 T%s H%s", t, h );
  outputString = "/room/temp ";
  outputString.concat(t);
  //outBuffer = outputString.c_str();
  // transmit and increment the counter

  // pause a second
  //delay(1000);
  //Serial.print(floatBuf1);
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C");
  Serial.println(radio.write(outputString.c_str(), outputString.length()+1), DEC);
  Serial.print("Wrote ");
  Serial.print(outputString.length()+1, DEC);
  Serial.println(" bytes");
  digitalWrite(13,1);
  delay(1000);
  digitalWrite(13,0);
  

}

