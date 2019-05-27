#include<LiquidCrystal.h>

// assigning all the lcd pins and declaring them to lcd object
const int rs = 9, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

// buzzer pin 
const int buzzer = 3;

// switches to control the alarm clock 
const int SetTime = 12, Increment = 2, Set_Alarm = 10, Ok = 11;

// vairables to store when to turn on the alarm
int alarmHour = 23, alarmMin = 59, alarmSec = 00;

// variables to constantly update the current time 
int Hour = 00, Min = 00, Sec = 00;

// variables to calculate if time has passed 1 sec
unsigned long startMillis; 
unsigned long currentMillis;
const unsigned long period = 1000; 

// Declaring User Made Functions
void Show_Time();
void Update_Time();
void SetCurrentTime();
void Setting_Alarm();
void Alarm();


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
  startMillis = millis(); 
}


void loop()
{ 
  Update_Time();
  Show_Time();
  if (digitalRead(SetTime) == 1)
  {
    SetCurrentTime();
  }
  if (digitalRead(Set_Alarm) == 1)  
  {    
    Setting_Alarm(); 
  }
  if (Hour == alarmHour && Min == alarmMin && Sec == alarmSec)
  {
    Alarm();
  }
}


void Show_Time()
{   
  lcd.setCursor(0,0);
  lcd.print(Hour);
  lcd.print(":");
  lcd.print(Min);
  lcd.print(":");
  lcd.print(Sec);
}

void Update_Time()
{
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    if (Sec > 59)
    {
      Sec = 0;
      Min++;

      if (Min > 59)
      {  
        Min = 0;
        Hour++;

        if (Hour > 23)
        { 
          Hour = 0;
        }
      }
    }
    else
    {
      Sec++;
    }
    
    startMillis = currentMillis; 
  } 
}


void SetCurrentTime()
{ 
  // setting current hour
  lcd.clear();
  
  //entering increment mode where hour is updated every time increment is pressed 
  while(digitalRead(Ok) == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("Set Hour: ");
    lcd.setCursor(0,1);
    lcd.print(Hour);
     
    if (digitalRead(Increment) == 1)
    {
      Hour++;
      
      if (Hour > 23)
      { 
        lcd.setCursor(0,1);
        lcd.print("  ");     // to remove the numbers that are left over on the screen. (say 23 to 0 should be 23 --> 0 not 03)
        Hour = 00;
      }
    }

    // as long as the button is pressed, it will only update time and increment only once
    while(digitalRead(Increment) == 1)
    {
      Update_Time();
    }
    Update_Time();
  } 

  // making sure the time isn't affected by user pressing a second or two long
  while(digitalRead(Ok) == 1)
  {
    Update_Time();
  }
   
  // setting current minute and repeating the above procedure except this time for minute
  lcd.clear();

  while(digitalRead(Ok) == 0)
  { 
    lcd.setCursor(0,0);
    lcd.print("Set Min:");
    lcd.setCursor(0,1);
    lcd.print(Min);
   
    if (digitalRead(Increment) == 1)
    {
      Min++;
      if (Min > 59)
      {  
        lcd.setCursor(0,1);
        lcd.print("  ");
        Min = 00;
      }
    }

    while(digitalRead(Increment) == 1)
    {
      Update_Time();
    }
    Update_Time();
  }

  while(digitalRead(Ok) == 1)
  {
    Update_Time();
  }

  lcd.clear();
  Show_Time();
}

// same as SetCurrentTime excpet this one is for alarm variables.
void Setting_Alarm()
{
  lcd.clear();

  while(digitalRead(Ok) == 0)
  { 
    lcd.setCursor(0,0);
    lcd.print("Set Alarm Hour:");
    lcd.setCursor(0,1);
    lcd.print(alarmHour);
     
    if (digitalRead(Increment) == 1)
    {    alarmHour++;
      if (alarmHour > 23)
      {  
        lcd.setCursor(0,1);
        lcd.print("  ");
        alarmHour = 00;
      }
    }

    while(digitalRead(Increment) == 1)
    {
      Update_Time();
    } 
    
    Update_Time();   
  }

  while(digitalRead(Ok) == 1)
  {
    Update_Time();
  }
  
  lcd.clear();

  while(digitalRead(Ok) == 0)
  { 
    lcd.setCursor(0,0);
    lcd.print("Set Alarm Min:");
    lcd.setCursor(0,1);
    lcd.print(alarmMin);
   
    if (digitalRead(Increment) == 1)
    { 
      alarmMin++;
      if (alarmMin > 59)
      {
        lcd.setCursor(0,1);
        lcd.print("  ");
        alarmMin = 00;
      }
    }
    
    while(digitalRead(Increment) == 1)
    {
      Update_Time();
    }
    Update_Time();    
  }

  while(digitalRead(Ok) == 1)
  {
    Update_Time();
  }

  lcd.clear();
  Show_Time();       
}


void Alarm()
{ 
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ALARM!!!");     
  while(digitalRead(Ok) == 0)
  {
    digitalWrite(3,HIGH);
    delay(500);
    digitalWrite(3,LOW);
    delay(500);
    Update_Time();
    Show_Time();      
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