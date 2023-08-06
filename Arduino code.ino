#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x38,16,2);

float vol = 0.0,Rate_1,Rate_2 = 6.7;// Taking flow sensor input 2 as constant because of proteus software limitations.
unsigned char flowsensor1 = 2; 
unsigned char flowsensor2 = 10;
float threshold = 2.0;



unsigned long currentTime;
unsigned long cloopTime;
unsigned long flow_frequency1;
unsigned long flow_frequency2;
LiquidCrystal lcd2(12, 11, 9, 6, 5, 4);

void flow1 () // Interrupt function to increment flow
{
   flow_frequency1++;
}
void flow2 () // Interrupt function to increment flow
{
   flow_frequency2++;
}

int sump=A0;
int qut=A1;
int hlf=A2;
int thf=A3;
int ful=3;
int motor=8;
int buz=7;
int s;
int q;
int h;
int t;
int f;
int i;     //motor status flag
int b=0;   //buzzer flag
int m=0;   //motor flag
int c=0;   //sump flag



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
   
  lcd1.init(); 
  lcd1.backlight();
  
pinMode(qut,INPUT);
pinMode(hlf,INPUT);
pinMode(qut,INPUT);
pinMode(ful,INPUT);
pinMode(sump,INPUT);
pinMode(motor,OUTPUT);
pinMode(buz,OUTPUT);
digitalWrite(buz,LOW);
}

void loop()
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

i=digitalRead(motor);
s=digitalRead(sump);
q=digitalRead(qut);
h=digitalRead(hlf);
t=digitalRead(thf);
f=digitalRead(ful);
lcd1.clear();

if(f==1 && t ==1 && h ==1 && q ==1 )
{
lcd1.setCursor(0,0);
lcd1.print(char(219));
lcd1.print(char(219));
lcd1.print(char(219));
lcd1.print(char(219));
lcd1.setCursor(5,0);
lcd1.print("FULL");
m=0;
b=0;
}
else
{
if(f ==0 && t ==1 && h ==1 && q ==1)
{
lcd1.setCursor(0,0);
lcd1.print(char(219));
lcd1.print(char(219));
lcd1.print(char(219));
lcd1.print("_");
lcd1.setCursor(5,0);
lcd1.print("3/4th");
b=0;
}
else
{
if(f ==0 && t ==0 && h ==1 && q ==1)
{
lcd1.setCursor(0,0);
lcd1.print(char(219));
lcd1.print(char(219));
lcd1.print("_");
lcd1.print("_");
lcd1.setCursor(5,0);
lcd1.print("HALF");
m=1;
b=0;
}
else
if(f ==0 && t ==0 && h ==0 && q ==1)
{
lcd1.setCursor(0,0);
lcd1.print(char(219));
lcd1.print("_");
lcd1.print("_");
lcd1.print("_");
lcd1.setCursor(5,0);
lcd1.print("1/4th");
b=0;
}
else
{
if(f ==0 && t ==0 && h ==0 && q ==0)
{
lcd1.setCursor(0,0);
lcd1.print("_");
lcd1.print("_");
lcd1.print("_");
lcd1.print("_");
lcd1.setCursor(5,0);
lcd1.print("LOW");
b=0;
}
else

{
digitalWrite(motor,LOW);
lcd1.setCursor(0,0);
lcd1.print("ERROR!");
b=1;
}
}}}
if(i==HIGH)
{
lcd1.setCursor(0,1);
lcd1.print("Pump ON");
}
else
{
lcd1.setCursor(0,1);
lcd1.print("Pump OFF");
}



if(s==1 && m==1)
{
digitalWrite(motor,HIGH);
}
if(s==0)
{
digitalWrite(motor,LOW);
lcd1.setCursor(11,0);
lcd1.print("Low");
lcd1.setCursor(11,1);
lcd1.print("Sump");
c=1;
}
if(s==1)
{
c=0;
}

if(m==0)
{
digitalWrite(motor,LOW);
}

if(b==1 || c==1)
{
digitalWrite(buz,HIGH);
delay(500);
digitalWrite(buz,LOW);
}
else
{
digitalWrite(buz,LOW);
}
delay(100);
lcd1.clear();

}
