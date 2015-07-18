#include "LedControl.h"
#include "font.h"

#define ARRAYCOLS 128
#define NUMARRAYS  8

LedControl lc = LedControl(12, 11, 10, NUMARRAYS);

/* we always wait a bit between updates of the display */
unsigned long delaytime = 500;

void setup() {
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
  Serial.begin(9600);
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
  int c,i, count;
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
    col = 7-(i % 8); //The column order is the reverse of the display order, so need to reverse it here by subtracting from 7.
    //i.e. col7 needs to be sent as col 1, etc. 
    lc.setColumn(array, col, buf[i]);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 94; i++)
  {
    //lc.setLed(3, i, i, true);
    //  lc.setRow(2, 2, 0xFFFF);
    //lc.setColumn(1, 2, 0xFF);
    //lc.setLed(0, i, i, true);
    
    printChar(String(millis(), DEC));
    delay(500);
  }
  for (int devices = 0; devices < NUMARRAYS; devices++) {
    lc.clearDisplay(devices);
  }

}
