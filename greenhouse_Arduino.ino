#include <dht.h>
#include<LiquidCrystal.h>
#include <SoftwareSerial.h>
 SoftwareSerial portOne(11,12);
#include "DHT.h"
#define dht_apin A0 // Analog Pin sensor is connected to
 #define light A1
 #define moisture A2
 #define lamb 8
 #define pump 9
 #define fan 10
 LiquidCrystal lcd(2,3,4,5,6,7);
 unsigned long oldTime;
 int l,t,h,mo,i=0,lt,mi;
 
 int mode=1;
 char str[10];
dht DHT;
int ti=0;
 int at=0;
 int R=0;
void setup(){
     lcd.begin(16,2);
  Serial.begin(9600);
      portOne.begin(9600);
  pinMode(lamb, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(fan, OUTPUT);
  delay(500);//Delay to let system boot
  digitalWrite(lamb,LOW);
  digitalWrite(pump,LOW);
  digitalWrite(fan,LOW);
 // Serial.println("DHT11 Humidity & temperature Sensor\n\n");
 // delay(1000);//Wait before accessing Sensor
 lcd.setCursor(0, 0);lcd.print("                ");
 lcd.setCursor(0, 1);lcd.print("                ");
 lcd.setCursor(11,0);  lcd.print("M");
}//end "setup()"
 
void loop(){
  if(mode==0)
  {lcd.setCursor(11,0);  lcd.print("A");
    }
    else
    {lcd.setCursor(11,0);  lcd.print("M");
      }
   while(Serial.available())
  {
    char ch=Serial.read();
    str[i++]=ch;
    if(ch=='*')
    {ti=1;
      }
  if((str[i-1]=='N')&&(ti==1))
    {
    R=1;
//lcd.setCursor(11,0);  lcd.print("A");
i=0;ti=0;

//     digitalWrite(relay00, HIGH);

   //  i=0;
   }    
    else if((str[i-1]=='Q')&&(ti==1))
    {
    mode=0;
lcd.setCursor(11,0);  lcd.print("A");
i=0;ti=0;

//     digitalWrite(relay00, HIGH);

   //  i=0;
   }
//
    else if((str[i-1]=='C')&&(ti==1))
   {
  mode=1;
   lcd.setCursor(11,0);  lcd.print("M");
i=0;ti=0;

    // digitalWrite(relay00, LOW);

    // i=0;
    }

    if((str[i-1]=='B')&&mode==1)
    {
    digitalWrite(fan, HIGH);i=0;  
//digitalWrite(relay01, HIGH);

      i=0;
    }
    else if((str[i-1]=='b')&&mode==1)
    {digitalWrite(fan, LOW);i=0;
     // digitalWrite(fan, HIGH);i=0;
//digitalWrite(relay01, LOW);

      i=0;
    }
     else if((str[i-1]=='L')&&mode==1)
    {
      
//digitalWrite(relay10, HIGH);
digitalWrite(lamb, HIGH);i=0;
      i=0;
    }
    else if((str[i-1]=='V')&&mode==1)
    {
      
//digitalWrite(relay10, HIGH);
digitalWrite(lamb, LOW);i=0;
      i=0;
    }
    else if((str[i-1]=='X')&&mode==1)
    {
      
//digitalWrite(relay10, HIGH);
digitalWrite(pump, HIGH);i=0;
      i=0;
    }
    else if((str[i-1]=='R')&&mode==1)
    {
      
//digitalWrite(relay10, HIGH);
digitalWrite(pump, LOW);i=0;
      i=0;
    }
    }
 // while(portOne.available())
//{
//char ch=portOne.read();

//str[i++]=ch;
/*if(str[i-1]=='F')
{
mode=1;
lcd.setCursor(11,0);  lcd.print("M");
i=0;
}

else if(str[i-1]=='f')
{
mode=0;
lcd.setCursor(11,0);  lcd.print("A");
i=0;
}*/
 /*if((str[i-1]=='B')&&mode==1)
{

digitalWrite(fan, HIGH);i=0;

}
else if((str[i-1]=='b')&&mode==1)
{
digitalWrite(fan, LOW);i=0;
}
else if((str[i-1]=='C')&&mode==1)
{
digitalWrite(lamb, HIGH);i=0;
}
else if((str[i-1]=='c')&&mode==1)
{
digitalWrite(lamb, LOW);i=0;
}
else if((str[i-1]=='D')&&mode==1)
{
digitalWrite(pump, HIGH);i=0;
}
else if((str[i-1]=='d')&&mode==1)
{
digitalWrite(pump, LOW);i=0;
}*/
//}
   DHT.read11(dht_apin);
   h=DHT.humidity;
   t=DHT.temperature;
   l=analogRead(A1);
   lt=l/10;
   mo=analogRead(A2);
   mi=mo/10;
  //Start of Program 
    lcd.setCursor(0,0);
  lcd.print("t:");
lcd.print(t);
 lcd.setCursor(6,0);
  lcd.print("H:");
lcd.print(h);
 lcd.print(" ");
 lcd.setCursor(0,1);
  lcd.print("L:");
  if (lt==100)
  {
  lcd.print(lt);
  }
  else if(lt>=10)
  { lcd.print("0");lcd.print(lt);
    }
      else 
    {lcd.print("00");lcd.print(lt);
      }
   lcd.setCursor(7,1);
  lcd.print("M:");
  if (mi>=100)
  {
  lcd.print("100");
  }
  else if(mi>=10)
  { lcd.print("0");lcd.print(mi);
    }
  
      else 
    {lcd.print("00");lcd.print(mi);
      }
  
  
if(mode==0)
{ 
  if(t>50)
     {digitalWrite(fan,HIGH);
     }
   else
     {digitalWrite(fan,LOW);
      }
    if(l<600)
     {digitalWrite(lamb,HIGH);
      }
    else
    {digitalWrite(lamb,LOW);
      }
    if(mo<350)
    {digitalWrite(pump,HIGH);
      }
    else
    {digitalWrite(pump,LOW);
     
      }
}     
// if((millis() - oldTime) > 2000)
//if(at>=100)
//Serial.print("*");
if(R==1)
{
  Serial.print("*");
if(mode==0)
{
  Serial.print("A");
}
else
{
  Serial.print("M");
}
Serial.print(t);Serial.print(h);
if (lt==100)
  {
  Serial.print(lt);
  }
  else if(lt>=10)
  { Serial.print("0");Serial.print(lt);
    }
    
      else 
    {Serial.print("00");Serial.print(lt);
      }
 
 
  if (mi>=100)
  {
  Serial.print(mi);
  }
  else if(mi>=10)
  { Serial.print("0");Serial.print(mi);
    }
   
      else 
    {Serial.print("00");Serial.print(mi);
      }
    R=0;  
}
if(at>=100){
if(mode==0)
{
  portOne.print("A");
}
else
{
 portOne.print("M");
}
portOne.print(t);portOne.print(h);
if (lt==100)
  {
  portOne.print(lt);
  }
  else if(lt>=10)
  { portOne.print("0");portOne.print(lt);
    }
   
      else 
    {portOne.print("00");portOne.print(lt);
      }
 
 
  if (mi>=100)
  {
  portOne.print(mi);
  }
  else if(mi>=10)
  { portOne.print("0");portOne.print(mi);
    }
    
      else 
    {portOne.print("00");portOne.print(mi);
    }
    at=0;
}
 at++;
 lcd.setCursor(14,1);
  lcd.print(at);
  }
 
  
    
  
