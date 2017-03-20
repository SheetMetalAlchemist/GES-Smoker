#include <SoftwareSerial.h>
int i = 0;

String t1;
String t2;
String t3;
String t4;
String inputStr1;
String inputStr2;
int divIndex;

// Attach the serial display's RX line to digital pin 2
SoftwareSerial lDisplay(3, 2); // pin 2 = TX, pin 3 = RX (unused)
SoftwareSerial lSens(5, 4); // pin 4 = TX (unused), pin 5 = RX
SoftwareSerial lSens2(7, 6); // pin 6 = TX (unused), pin 7 = RX

void setup()
{
  lSens.begin(9600);
  lSens2.begin(9600);
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
  //READ FROM BOARD 1
  lSens.listen();
  inputStr1 = lSens.readStringUntil(13);
  divIndex = inputStr1.indexOf("]", 2);
  t1 = inputStr1.substring(1, divIndex - 1);
  t2 = inputStr1.substring(divIndex + 1, inputStr1.length() - 1);

  delay(250);

  //READ FROM BOARD 2
  lSens2.listen();
  inputStr2 = lSens2.readStringUntil(13);
  divIndex = inputStr2.indexOf("]", 2);
  t3 = inputStr2.substring(1, divIndex - 1);
  t4 = inputStr2.substring(divIndex + 1, inputStr2.length() - 1);

  delay(250);

  //START DISPLAYING STUFF
  lDisplay.write(254); // move cursor to 13th position, line #1
  lDisplay.write(140);
  char T1toWrite[5];
  t1 = cToF(t1);
  t1.toCharArray(T1toWrite, 5);

  Serial.print("T1: ");
  Serial.write(T1toWrite);
  Serial.println();

  lDisplay.write(T1toWrite);

  lDisplay.write(254); // move cursor to 13th position, line #2
  lDisplay.write(204);
  char T2toWrite[5];
  t2 = cToF(t2);
  t2.toCharArray(T2toWrite, 5);

  Serial.print("T2: ");
  Serial.write(T2toWrite);
  Serial.println();
  lDisplay.write(T2toWrite);

  char T3toWrite[5];
  t3 = cToF(t3);
  t3.toCharArray(T3toWrite, 5);

  Serial.print("T3: ");
  Serial.write(T3toWrite);
  Serial.println();

  char T4toWrite[5];
  t4 = cToF(t4);
  t4.toCharArray(T4toWrite, 5);

  Serial.print("T4: ");
  Serial.write(T4toWrite);
  Serial.println();
}

String cToF(String inputT) {
  float inputCtemp = inputT.toFloat();
  float Ftemp = inputCtemp * 1.8 + 32;
  String outputFTemp = String(Ftemp, 1);
  return outputFTemp;
}

