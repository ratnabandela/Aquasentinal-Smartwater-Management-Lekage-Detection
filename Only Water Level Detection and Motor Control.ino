#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x38,16,2);

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
  lcd.init(); 
  lcd.backlight();
  
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

i=digitalRead(motor);
s=digitalRead(sump);
q=digitalRead(qut);
h=digitalRead(hlf);
t=digitalRead(thf);
f=digitalRead(ful);
lcd.clear();

if(f==1 && t ==1 && h ==1 && q ==1 )
{
lcd.setCursor(0,0);
lcd.print(char(219));
lcd.print(char(219));
lcd.print(char(219));
lcd.print(char(219));
lcd.setCursor(5,0);
lcd.print("FULL");
m=0;
b=0;
}
else
{
if(f ==0 && t ==1 && h ==1 && q ==1)
{
lcd.setCursor(0,0);
lcd.print(char(219));
lcd.print(char(219));
lcd.print(char(219));
lcd.print("_");
lcd.setCursor(5,0);
lcd.print("3/4th");
b=0;
}
else
{
if(f ==0 && t ==0 && h ==1 && q ==1)
{
lcd.setCursor(0,0);
lcd.print(char(219));
lcd.print(char(219));
lcd.print("_");
lcd.print("_");
lcd.setCursor(5,0);
lcd.print("HALF");
m=1;
b=0;
}
else
if(f ==0 && t ==0 && h ==0 && q ==1)
{
lcd.setCursor(0,0);
lcd.print(char(219));
lcd.print("_");
lcd.print("_");
lcd.print("_");
lcd.setCursor(5,0);
lcd.print("1/4th");
b=0;
}
else
{
if(f ==0 && t ==0 && h ==0 && q ==0)
{
lcd.setCursor(0,0);
lcd.print("_");
lcd.print("_");
lcd.print("_");
lcd.print("_");
lcd.setCursor(5,0);
lcd.print("LOW");
b=0;
}
else

{
digitalWrite(motor,LOW);
lcd.setCursor(0,0);
lcd.print("ERROR!");
b=1;
}
}}}
if(i==HIGH)
{
lcd.setCursor(0,1);
lcd.print("Pump ON");
}
else
{
lcd.setCursor(0,1);
lcd.print("Pump OFF");
}



if(s==1 && m==1)
{
digitalWrite(motor,HIGH);
}
if(s==0)
{
digitalWrite(motor,LOW);
lcd.setCursor(11,0);
lcd.print("Low");
lcd.setCursor(11,1);
lcd.print("Sump");
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
lcd.clear();
}
