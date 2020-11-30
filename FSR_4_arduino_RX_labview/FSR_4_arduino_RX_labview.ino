/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() 
{  lcd.begin(20,4);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() 
{
   serialEvent(); //call the function
  // print the string when a newline arrives:
  //lcd.clear();
   
  if (stringComplete)
  {
    lcd.setCursor(0,0);
  lcd.write(inputString[0]);
  lcd.write(inputString[1]);
  lcd.write(inputString[2]);
  lcd.write(inputString[3]);
  lcd.write(inputString[4]);
  lcd.write(inputString[5]);
  lcd.write(inputString[6]);
 
  lcd.setCursor(0,1);
  lcd.write(inputString[7]);
  lcd.write(inputString[8]);
  lcd.write(inputString[9]);
  lcd.write(inputString[10]);
  lcd.write(inputString[11]);
  lcd.write(inputString[12]);
  lcd.write(inputString[13]);
  
  lcd.setCursor(0,2);
  lcd.write(inputString[14]);
  lcd.write(inputString[15]);
  lcd.write(inputString[16]);
  lcd.write(inputString[17]);
  lcd.write(inputString[18]);
  lcd.write(inputString[19]);
  lcd.write(inputString[20]);

  lcd.setCursor(0,3);
  
  lcd.write(inputString[21]);
  lcd.write(inputString[22]);
  lcd.write(inputString[23]);
  lcd.write(inputString[24]);
  lcd.write(inputString[25]);
  lcd.write(inputString[26]);
  lcd.write(inputString[27]);
 
    
  delay(500);
   
 /* Serial.print(inputString[0]);
  Serial.print(inputString[1]);
  Serial.print(inputString[2]);
  Serial.print(inputString[3]);
  Serial.print(inputString[4]);
  Serial.print(inputString[5]);
  Serial.print(inputString[6]); 
  Serial.print(inputString[7]);
  Serial.print(inputString[8]);
  Serial.print(inputString[9]);
  Serial.print(inputString[10]);
  Serial.print(inputString[11]);
  Serial.print(inputString[12]);
  Serial.print(inputString[13]); 
  Serial.print(inputString[14]);
  Serial.print(inputString[15]);
  Serial.print(inputString[16]);
  Serial.print(inputString[17]);
  Serial.print(inputString[18]);
  Serial.print(inputString[19]);
  Serial.print(inputString[20]);
  Serial.print(inputString[21]);
  Serial.print(inputString[22]);
  Serial.print(inputString[23]);
  Serial.print(inputString[24]);
  Serial.print(inputString[25]);
  Serial.print(inputString[26]);
  Serial.println(inputString[27]); */ 
 // Serial.println(inputString[31]);
    // clear the string:
    Serial.println(inputString); 
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent()
{
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 0x0D)
    {
      stringComplete = true;
    }
  }
}
