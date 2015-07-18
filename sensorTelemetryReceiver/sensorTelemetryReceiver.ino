// Read data from DHT22 over radio link
//
//Based loosely on pingpair.ino

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(9, 10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };


void setup(void)
{


  Serial.begin(57600);
  Serial.println("Working");
  //
  // Setup and configure rf radio
  //

  radio.begin();
    radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x4c);
  radio.setRetries(15, 15);
  radio.enableDynamicPayloads();
   radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL); // pipes[0]);
  printf_begin();
  radio.startListening();
  
  radio.powerUp();
 
  delay(20);
  radio.printDetails();
  delay(20);
  Serial.println("Initialised");
}

void loop(void)
{
  Serial.print(".");
  // if there is data ready
  if ( radio.available() )
  {
    Serial.println("Radio.Available");
    // Dump the payloads until we've gotten everything
    String got_time;
    bool done = false;
    while (!done)
    {
      // Fetch the payload, and see if this was the last one.
      done = true;
      radio.read( &got_time, radio.getDynamicPayloadSize() );

      Serial.print("Got ");
      Serial.println(got_time);

      // Delay just a little bit to let the other unit
      // make the transition to receiver
      delay(20);
    }

    // First, stop listening so we can talk
    //radio.stopListening();

    // Send the final one back.
   // radio.write( &got_time, sizeof(unsigned long) );
    //printf("Sent response.\n\r");

    // Now, resume listening so we catch the next packets.
    radio.startListening();
   
  }
  delay(100);
}

