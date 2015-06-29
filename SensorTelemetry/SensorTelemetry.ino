#include <SPI.h>
#include <RF24.h>
#include "DHT.h"


// ce,csn pins
RF24 radio(9,10);


//Temp Sensors
DHT sens1(2, DHT22);
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

  sens1.begin();
  //sens2.begin();

  Serial.begin(57600);
  while(!Serial);
  Serial.println("Initialised");

}

void loop(void)
{
  // 32 bytes is maximum payload
  char outBuffer[32]= "";
  char floatBuf1[10];
  char floatBuf2[10];
  float h, t;
  h = sens1.readHumidity();
  t = sens1.readTemperature();

  dtostrf(h, 6, 2, floatBuf1);
  dtostrf(t, 6, 2, floatBuf2);
  // pad numbers and convert to string
  sprintf(outBuffer,"S1 T%s H%s", t, h );

  // transmit and increment the counter

  // pause a second
  delay(1000);
  Serial.print(floatBuf1);
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C");
  radio.write(outBuffer, strlen(outBuffer));

  delay(1000);

  

}

