
#include <LiquidCrystal.h>

float vol = 0.0,Rate_1,Rate_2 = 6.7;// Taking flow sensor input 2 as constant because of proteus software limitations.
unsigned char flowsensor1 = 2; 
unsigned char flowsensor2 = 7;
float threshold = 2.0;

unsigned long currentTime;
unsigned long cloopTime;
unsigned long flow_frequency1;
unsigned long flow_frequency2;
LiquidCrystal lcd2(12, 11, 6, 5, 4, 3);

void flow1 () // Interrupt function to increment flow
{
   flow_frequency1++;
}
void flow2 () // Interrupt function to increment flow
{
   flow_frequency2++;
}
void setup()
{
   Serial.begin(9600);
   pinMode(flowsensor1, INPUT);
   digitalWrite(flowsensor1, HIGH); // Optional Internal Pull-Up
   attachInterrupt(digitalPinToInterrupt(flowsensor1), flow1, RISING); // Setup Interrupt
   
   pinMode(flowsensor2, INPUT);
   digitalWrite(flowsensor2, HIGH); // Optional Internal Pull-Up
   attachInterrupt(digitalPinToInterrupt(flowsensor2), flow2, RISING); // Setup Interrupt

   lcd2.begin(16, 2);
   lcd2.clear();
   lcd2.setCursor(0,0);
   lcd2.print("Water FlowMeter");
   lcd2.setCursor(0,1);
   lcd2.print("   sensing...  ");
   delay(500);
   currentTime = millis();
   cloopTime = currentTime;
}

void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency1 != 0)
    {
      
       Rate_1 = (flow_frequency1 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
       //Rate_2 = (flow_frequency2 / 7.5);
       if((Rate_2 - Rate_1) < threshold)
       {
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("R1: ");
      lcd2.print(Rate_1);
      lcd2.print("L/M ");
      //lcd2.print("R2: ");
      //lcd2.print(Rate_2);
      //lcd2.print("L/M");      
      Rate_1 = Rate_1/60;
            
      lcd2.setCursor(0,1);
      vol = vol +Rate_1;
      lcd2.print("No Leakage Detected");
      //lcd2.print(" Vol")
      //lcd2.print(vol);
      //lcd2.print(" L");
      flow_frequency1 = 0; // Reset Counter
      flow_frequency2 = 0;
      Serial.print(Rate_1, DEC); // Print litres/hour
      Serial.println(" L/Sec");
      Serial.print(Rate_2, DEC); // Print litres/hour
      Serial.println(" L/Sec");
       }
       else {
           lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Rate1: ");
      lcd2.print(Rate_1);
      lcd2.print(" L/M");
      //lcd2.print("Rate2: ");
      //lcd2.print(Rate_2);
      //lcd2.print(" L/M");      
      Rate_1 = Rate_1/60;
            
      lcd2.setCursor(0,1);
      vol = vol +Rate_1;
      lcd2.print("Leakage Detected");
      flow_frequency1 = 0; // Reset Counter
      flow_frequency2 = 0;
      Serial.print(Rate_1, DEC); // Print litres/hour
      Serial.println(" L/Sec");
      Serial.print(Rate_2, DEC); // Print litres/hour
      Serial.println(" L/Sec");
       }
    }
    else {
      Serial.println(" flow rate = 0 ");
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Rate: ");
      lcd2.print( flow_frequency1 );
      lcd2.print(" L/M");
      lcd2.setCursor(0,1);
      lcd2.print("No Water Flow");
      //lcd2.print("Vol:");
      //lcd2.print(vol);
      //lcd2.print(" L");
    }
   }
}
