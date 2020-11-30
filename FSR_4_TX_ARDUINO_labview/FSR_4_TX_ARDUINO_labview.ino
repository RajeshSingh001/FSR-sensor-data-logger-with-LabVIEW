/* FSR testing sketch. 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int fsrPin1 = 0;     // the FSR and 10K pulldown are connected to a0
int fsrPin2 = 1;
int fsrPin3 = 2;
int fsrPin4 = 3;

int fsrReading1;     // the analog reading from the FSR resistor divider
int fsrReading2;
int fsrReading3;
int fsrReading4; 

int fsrVoltage1;     // the analog reading converted to voltage
int fsrVoltage2;
int fsrVoltage3;
int fsrVoltage4;
unsigned long fsrResistance1;  // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrResistance2;
unsigned long fsrResistance3;
unsigned long fsrResistance4;
unsigned long fsrConductance1;
unsigned long fsrConductance2;
unsigned long fsrConductance3;
unsigned long fsrConductance4;

long fsrForce1;       // Finally, the resistance converted to force
long fsrForce2;
long fsrForce3;
long fsrForce4;
 
void setup(void)
{ 
  lcd.begin(16,4);
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}
 
void loop(void)
{
  fsrReading1 = analogRead(fsrPin1); 
  fsrReading2 = analogRead(fsrPin2); 
  fsrReading3 = analogRead(fsrPin3); 
  fsrReading4 = analogRead(fsrPin4); 
 /* Serial.print("Analog reading1 = ");
  Serial.println(fsrReading1);
   Serial.print("Analog reading2 = ");
  Serial.println(fsrReading2);
   Serial.print("Analog reading3 = ");
  Serial.println(fsrReading3);
   Serial.print("Analog reading4 = ");
  Serial.println(fsrReading4);*/
 
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  fsrVoltage1 = map(fsrReading1, 0, 1023, 5000, 0);
  fsrVoltage2 = map(fsrReading2, 0, 1023, 5000, 0);
  fsrVoltage3 = map(fsrReading3, 0, 1023, 5000, 0);
  fsrVoltage4 = map(fsrReading4, 0, 1023, 5000, 0);
 /* Serial.print("Voltage reading1 in mV = ");
  Serial.println(fsrVoltage1); 
 Serial.print("Voltage reading2 in mV = ");
  Serial.println(fsrVoltage2); 
  Serial.print("Voltage reading3 in mV = ");
  Serial.println(fsrVoltage3);
  Serial.print("Voltage reading4 in mV = ");
  Serial.println(fsrVoltage4);*/
 
  if ((fsrVoltage1 == 0)||(fsrVoltage2 == 0)||(fsrVoltage3 == 0)||(fsrVoltage4 == 0))
  {
    lcd.clear();
    lcd.print("No pressure");
    //Serial.println("No pressure");  
  } 
  
  else 
  {
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance1 = 5000 - fsrVoltage1;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance1 *= 10000;                // 10K resistor
    fsrResistance1 /= fsrVoltage1;
    
    fsrResistance2 = 5000 - fsrVoltage2;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance2 *= 10000;                // 10K resistor
    fsrResistance2 /= fsrVoltage2;
    
    fsrResistance3 = 5000 - fsrVoltage3;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance3 *= 10000;                // 10K resistor
    fsrResistance3 /= fsrVoltage3;
    
    fsrResistance4 = 5000 - fsrVoltage4;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance4 *= 10000;                // 10K resistor
    fsrResistance4 /= fsrVoltage4;
    
   /* Serial.print("FSR resistance1 in ohms = ");
    Serial.println(fsrResistance1);
    
    Serial.print("FSR resistance2 in ohms = ");
    Serial.println(fsrResistance2);
    
    Serial.print("FSR resistance3 in ohms = ");
    Serial.println(fsrResistance3);
    
    Serial.print("FSR resistance4 in ohms = ");
    Serial.println(fsrResistance4);*/
 
    fsrConductance1 = 1000000;           // we measure in micromhos so 
    fsrConductance1 /= fsrResistance1;
    
    fsrConductance2 = 1000000;           // we measure in micromhos so 
    fsrConductance2 /= fsrResistance2;
    
    fsrConductance3 = 1000000;           // we measure in micromhos so 
    fsrConductance3 /= fsrResistance3;
    
    fsrConductance4 = 1000000;           // we measure in micromhos so 
    fsrConductance4 /= fsrResistance4;
    
    /*Serial.print("Conductance1 in microMhos: ");
    Serial.println(fsrConductance1);
    
     Serial.print("Conductance2 in microMhos: ");
    Serial.println(fsrConductance2);
    
     Serial.print("Conductance3 in microMhos: ");
    Serial.println(fsrConductance3);
    
     Serial.print("Conductance4 in microMhos: ");
    Serial.println(fsrConductance4);*/
 
    // Use the two FSR guide graphs to approximate the force
    if ((fsrConductance1 <= 1000)|| (fsrConductance2 <= 1000)|| (fsrConductance3 <= 1000)|| (fsrConductance4 <= 1000))
    {
      lcd.clear();
      fsrForce1 = fsrConductance1 / 80;
      fsrForce2 = fsrConductance2 / 80;
      fsrForce3 = fsrConductance3 / 80;
      fsrForce4 = fsrConductance4 / 80;
      
      fsrForce1=fsrForce1+10;
      fsrForce2=fsrForce2+10;
      fsrForce3=fsrForce3+10;
      fsrForce4=fsrForce4+10;
      /*Serial.print("Force1 in Newtons: ");
      Serial.println(fsrForce1);*/
      lcd.setCursor(0,0);
      lcd.print("FSR1:");
      lcd.print(fsrForce1); 
      
      /*Serial.print("Force2 in Newtons: ");
      Serial.println(fsrForce2);*/
      lcd.setCursor(0,1);
      lcd.print("FSR2:");
      lcd.print(fsrForce2);
      
      /*Serial.print("Force3 in Newtons: ");
      Serial.println(fsrForce3);*/
      lcd.setCursor(0,2);
      lcd.print("FSR3:");
      lcd.print(fsrForce3);
      
      /*Serial.print("Force4 in Newtons: ");
      Serial.println(fsrForce4);*/
      lcd.setCursor(0,3);
      lcd.print("FSR4:");
      lcd.print(fsrForce4);
      
      
      Serial.print("FSR1:");
      Serial.print(fsrForce1);
      Serial.print("FSR2:");
      Serial.print(fsrForce2);
      Serial.print("FSR3:");
      Serial.print(fsrForce3);
      Serial.print("FSR4:");
      Serial.println(fsrForce4);
      
    } 
    else 
    { 
      lcd.clear();
      fsrForce1 = fsrConductance1 - 1000;
      fsrForce1 /= 30;
      
      fsrForce2 = fsrConductance2 - 1000;
      fsrForce2 /= 30;
      
      fsrForce3 = fsrConductance3 - 1000;
      fsrForce3 /= 30;
      
      fsrForce4 = fsrConductance4 - 1000;
      fsrForce4 /= 30;
      
      fsrForce1=fsrForce1+10;
      fsrForce2=fsrForce2+10;
      fsrForce3=fsrForce3+10;
      fsrForce4=fsrForce4+10;
      /*Serial.print("Force1 in Newtons: ");
      Serial.println(fsrForce1);*/
       lcd.setCursor(0,0);
      lcd.print("FSR1:");
      lcd.print(fsrForce1); 
      
      /*Serial.print("Force2 in Newtons: ");
      Serial.println(fsrForce2);*/
      lcd.setCursor(0,1);
      lcd.print("FSR2:");
      lcd.print(fsrForce2);
      
      /*Serial.print("Force3 in Newtons: ");
      Serial.println(fsrForce3);*/
      lcd.setCursor(0,2);
      lcd.print("FSR3:");
      lcd.print(fsrForce3);
      
      /*Serial.print("Force4 in Newtons: ");
      Serial.println(fsrForce4);*/
      lcd.setCursor(0,3);
      lcd.print("FSR4:");
      lcd.print(fsrForce4);
      
      
      Serial.print("FSR1:");
      Serial.print(fsrForce1);
      Serial.print("FSR2:");
      Serial.print(fsrForce2);
      Serial.print("FSR3:");
      Serial.print(fsrForce3);
       Serial.print("FSR4:");
      Serial.println(fsrForce4);
    }
  }
      //Serial.println("--------------------");
      delay(1000);
}
