#include <SoftwareSerial.h>
int i = 0;
char iSerial[10];

// Attach the serial display's RX line to digital pin 2
SoftwareSerial lDisplay(3, 2); // pin 2 = TX, pin 3 = RX (unused)
SoftwareSerial lSens(5,4); // pin 4 = TX (unused), pin 5 = RX

void setup()
{
  lDisplay.begin(9600); // set up serial port for 9600 baud
  lSens.begin(9600);
  delay(500); // wait for display to boot up

  lDisplay.write(254); // move cursor to beginning of first line
  lDisplay.write(128);
}

void loop()
{
  //i++;
  lSens.listen();
  char lTemp = lSens.read();
  Serial.println(lTemp);
  delay(500);
/*
  lDisplay.write(254); // move cursor to 13th position, line #1
  lDisplay.write(140);
*/
  lDisplay.write(iSerial);
/*
  lDisplay.write(254); // move cursor to 13th position, line #2
  lDisplay.write(204);

  lDisplay.write(iSerial);
  delay(1000);*/
}

