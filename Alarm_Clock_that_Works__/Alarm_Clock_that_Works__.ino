#include<LiquidCrystal.h>
const int rs=9;
const int en=8;
const int d4=4;
const int d5=5;
const int d6=6;
const int d7=7;
const int buzzer=3;
const int SetTime=12;   //switch
const int Increment=2;  // switch
const int Set_Alarm=10; // switch 
const int Ok=11;        //switch
int alarmHour=23;
int alarmMin=59;
int alarmSec=00;
int Hour=00;
int Min=00;
int Sec=00;
unsigned long startMillis; 
unsigned long currentMillis;
const unsigned long period=1000; 

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void Show_Time()
{   lcd.setCursor(0,0);
    lcd.print(Hour);
    lcd.print(":");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    
        
}

void Show_Time_Alarm()
{   lcd.setCursor(0,0);
    lcd.print(Hour);
    lcd.print(":");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    


    lcd.setCursor(0,1);
    lcd.print("Alarm");
    
      
}

void Update_Time()
{
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
    {
        if (Sec>59)
          {
             Sec=0;
             Min++;
             if (Min>59)
             {  Min=0;
                Hour++;
                if (Hour>23)
                   { Hour=0;}
             }
              
          }
        else
        Sec++;
        startMillis=currentMillis; 
    }
   
 
}

void SetCurrentTime()
{ lcd.clear();
  while(digitalRead(Ok)==0)
    {
         
     lcd.setCursor(0,0);
     lcd.print("Set Hour: ");
     lcd.setCursor(0,1);
     lcd.print(Hour);
     
     if (digitalRead(Increment)==1)
     {
         Hour++;
         if (Hour>23)
         {  lcd.setCursor(0,1);
            lcd.print("  ");
            Hour=00;
         }
     }
     while(digitalRead(Increment)==1)
     {Update_Time();}
     Update_Time();
   } 
  while(digitalRead(Ok)==1)
  {Update_Time();}
   
  lcd.clear();
  while(digitalRead(Ok)==0)
   { 
     
     lcd.setCursor(0,0);
     lcd.print("Set Min:");
     lcd.setCursor(0,1);
     lcd.print(Min);
     
     if (digitalRead(Increment)==1)
     {
         Min++;
     if (Min>59)
     {  lcd.setCursor(0,1);
            lcd.print("  ");
            Min=00;
         }
     }
     while(digitalRead(Increment)==1)
     {Update_Time();}
     Update_Time();
   }

  while(digitalRead(Ok)==1)
  {Update_Time();}     
  
/*   lcd.clear();
  while(digitalRead(Ok)==0)
   { 
     
     lcd.setCursor(0,0);
     lcd.print("Set Sec:");
     lcd.setCursor(0,1);
     lcd.print(Sec);
     
     if (digitalRead(Increment)==1){
         Sec++;
     if (Sec>59)
         {  lcd.setCursor(0,1);
            lcd.print("  ");
            Sec=00;
         } }
     while(digitalRead(Increment)==1)
     {Update_Time();}  
     Update_Time();       
   }
  while(digitalRead(Ok)==1)
  {Update_Time();}      */ 
   lcd.clear();
   Show_Time();
}

void Setting_Alarm()
{
  lcd.clear();
  while(digitalRead(Ok)==0)
   { 
     lcd.setCursor(0,0);
     lcd.print("Set Alarm Hour:");
     lcd.setCursor(0,1);
     lcd.print(alarmHour);
     
     if (digitalRead(Increment)==1)
     {    alarmHour++;
     if (alarmHour>23)
         {  lcd.setCursor(0,1);
            lcd.print("  ");
            alarmHour=00;
         }
      }
     while(digitalRead(Increment)==1)
     {Update_Time();} 
     Update_Time();   
   } 
  while(digitalRead(Ok)==1)
  {Update_Time();}
  
  lcd.clear();
  while(digitalRead(Ok)==0)
   { 
     
     lcd.setCursor(0,0);
     lcd.print("Set Alarm Min:");
     lcd.setCursor(0,1);
     lcd.print(alarmMin);
     
     if (digitalRead(Increment)==1)
     {    alarmMin++;
     if (alarmMin>59)
        {
         lcd.setCursor(0,1);
         lcd.print("  ");
         alarmMin=00;
        }
      }
     while(digitalRead(Increment)==1)
     {Update_Time();}
     Update_Time();    
   }    
   while(digitalRead(Ok)==1)
   {Update_Time();}

 /* lcd.clear();
  while(digitalRead(Ok)==0)
   { 
     lcd.setCursor(0,0);
     lcd.print("Set Alarm Sec:");
     lcd.setCursor(0,1);
     lcd.print(alarmSec);
     
     if (digitalRead(Increment)==1)
     {    alarmSec++;
          if (alarmSec>59)
          {  lcd.setCursor(0,1);
             lcd.print("  ");
             alarmSec=00;
           }
      }
     while(digitalRead(Increment)==1)
     {Update_Time();}    
     Update_Time();
   } 
   
  while(digitalRead(Ok)==1)
  {Update_Time();} */
   
   lcd.clear();
   Show_Time();       
   
}

void Alarm()
{ lcd.clear();
  while(digitalRead(Ok)==0)
  {
      digitalWrite(3,HIGH);
      delay(500);
      digitalWrite(3,LOW);
      delay(500);
      Update_Time();
      Show_Time_Alarm();
      
  }
  lcd.clear();
  while(digitalRead(Ok)==1)
  {
      digitalWrite(buzzer,HIGH);
      Update_Time();

  }
  lcd.clear();
  Show_Time();
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(buzzer,OUTPUT);
  pinMode(SetTime,INPUT);
  pinMode(Increment,INPUT);
  pinMode(Set_Alarm,INPUT);
  pinMode(Ok,INPUT);
  digitalWrite(buzzer,HIGH);
  delay(1000);
  startMillis=millis(); 
}



void loop()
{ Update_Time();
  Show_Time();
  if (digitalRead(SetTime)==1)
  {
    SetCurrentTime();
  }
  if (digitalRead(Set_Alarm)==1)  
  {    
    Setting_Alarm(); 
  }
  if (Hour==alarmHour && Min==alarmMin && Sec==alarmSec)
       Alarm();
}
  


