#include <SoftwareSerial.h>
int i = 0;

char t1[5];
char t2[5];
char crap[5];
char T1toWrite[5];
char T2toWrite[5];

String tempStr;
String tempStr2;
String tempStr2T;


// Attach the serial display's RX line to digital pin 2
SoftwareSerial lDisplay(3, 2); // pin 2 = TX, pin 3 = RX (unused)
SoftwareSerial lSens(5,4); // pin 4 = TX (unused), pin 5 = RX

void setup()
{
  lSens.begin(9600);
  lDisplay.begin(9600); // set up serial port for 9600 baud
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  delay(500); // wait for display to boot up

  lDisplay.write(254); // move cursor to beginning of first line
  lDisplay.write(128);

  lDisplay.write("T(L) BACK:      "); // clear display + legends
  lDisplay.write("T(L) FRONT:     ");
}

void loop()
{
  lSens.listen();
  while (lSens.available() > 0) {
    lSens.readBytesUntil(93,crap,1);
    //lSens.readBytesUntil(93,crap,1);
    lSens.readBytesUntil(93,t1,5);
    lSens.readBytesUntil(93,crap,1);
    lSens.readBytesUntil(93,t2,5);
    tempStr = t1;
    tempStr2 = t2;
    tempStr2T = tempStr2.substring(0,5);
    
    Serial.print("T1: ");
    Serial.println(tempStr);
    Serial.print("T2: ");
    Serial.println(tempStr2T);
    delay(50);
  }

  lDisplay.write(254); // move cursor to 13th position, line #1
  lDisplay.write(139);
  //tempStr.toCharArray(T1toWrite, 5);

  lDisplay.write(t1);

  lDisplay.write(254); // move cursor to 13th position, line #2
  lDisplay.write(203);
  tempStr2T.toCharArray(T2toWrite, 5);
  lDisplay.write(T2toWrite);
  
  delay(600);
}

