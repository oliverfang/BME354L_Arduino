#include <LiquidCrystal.h>

//Initialize LCD Pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Define pins
int buttonPin = A0;
int buttonLast = 0;
int buttonVal = 0;

//Define ADC buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

unsigned long now = 0;
unsigned long last = 0;
unsigned long currTime = 0;

int timerMode = 1;

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{
  if(timerMode == 1) //timer is in run mode
  {
    lcd.setCursor(0, 1);
    lcd.print(timerMode); //print timer mode to LCD screen
    now = millis(); //get the total time elapsed now
    currTime += (now-last); //add the elapsed time since last time we checked currTime
    last = now; //update/check the last time
    lcd.setCursor(0,0);
    updateLCD(currTime); //update the LCD
    //Serial.println(getButtonPress());
    buttonVal = getButtonPress(); //check if a button was pressed
    if (buttonVal == btnSELECT && buttonLast != btnSELECT) //if the SELECT button was pressed
    {
      timerMode = 0; //switch timer mode to stop
      buttonLast = btnSELECT; //change the last button to SELECT (used for debouncing)
    }
    else if (buttonVal != btnSELECT)
    {
      buttonLast = 0; //otherwise set to default
    }
  }
  if(timerMode == 0)
  {
    lcd.setCursor(0, 1);
    lcd.print(timerMode); //print timer mode to LCD screen
    buttonVal = getButtonPress(); //check if a button was pressed
    if (buttonVal == btnSELECT && buttonLast != btnSELECT) //if the SELECT button was pressed
    {
      timerMode = 1; //switch timer mode to run
      buttonLast = btnSELECT; //change the last button to SELECT
    }
    else if (buttonVal != btnSELECT)
    {
      buttonLast = 0; //otherwise set to default
    }
    last = millis(); //important: update the last time so we only add time elapsed while in timer mode 1
  }
}

int getButtonPress()
{
  int adcIn;
  adcIn = analogRead(buttonPin);
  delay(5); 
  if (adcIn < 50) return btnRIGHT;
  else if (adcIn < 195) return btnUP;
  else if (adcIn < 380) return btnDOWN;
  else if (adcIn < 555) return btnLEFT;
  else if (adcIn < 790) return btnSELECT;
  else return btnNONE; 
}

void updateLCD(long time) //input is in milliseconds
{
  lcd.setCursor(0, 0); //move cursor to initial position
  if (time / (60000) < 10) //if less than 10 minutes
  {
    lcd.print(" "); //print a space 
  }
  lcd.print(time / 60000);
  lcd.print(":");
  //print seconds
  if (time % (60000) >= 10000) //60000 milliseconds in a minute
  {
    lcd.print((time % 60000) / 1000);
  }
  else
  {
    lcd.print("0"); //print an extra 0 if number is less than 10 seonds
    lcd.print((time % 60000) / 1000);
  }
  lcd.print(":");
  //print the milliseconds (only first 2 digits)
  if (time % 1000 >= 100) 
  {
    lcd.print((time % 1000) / 10); 
  }
  else
  {
    lcd.print("0"); //print an extra 0 if less than 100 milliseconds
    lcd.print((time % 1000) / 10);
  }
  
}

