
/********************************************************
 * PID RelayOutput Example
 * Same as basic example, except that this time, the output
 * is going to a digital pin which (we presume) is controlling
 * a relay.  The pid is designed to output an analog value,
 * but the relay can only be On/Off.
 *
 *   To connect them together we use "time proportioning
 * control"  Tt's essentially a really slow version of PWM.
 * First we decide on a window size (5000mS say.) We then 
 * set the pid to adjust its output between 0 and that window
 * size.  Lastly, we add some logic that translates the PID
 * output into "Relay On Time" with the remainder of the 
 * window being "Relay Off Time"
 ********************************************************/

#include <PID_v1.h>
#define RelayPin 6
#define ThermocouplePin A0

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
//kp = 2 (proportional gain - difference between the current temperature and the set point)
//ki = 5 (integral gain - proportional to the magnitude and duration of error)
//kd = 1 (derivative gain - slope of the error over time)
PID myPID(&Input, &Output, &Setpoint, 2, 5, 1, DIRECT); 

//WindowSize is essentially the period of the PWM
int WindowSize = 500;
unsigned long windowStartTime;

void setup()
{
  pinMode(RelayPin, OUTPUT);
  windowStartTime = millis(); //set to milliseconds

  PIDsetup(200, WindowSize);

  Serial.begin(9600);
}

void loop()
{
  Input = analogRead(ThermocouplePin);
  myPID.Compute();

  //turn the output pin on/off based on pid output
  unsigned long now = millis();

  if(now - windowStartTime>WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
    Serial.print("Temperature: ");
    Serial.println(analogRead(ThermocouplePin));

    Serial.print("Output: ");
    Serial.println(Output);
  }
  
  if(Output > now - windowStartTime) 
  {
    digitalWrite(RelayPin, HIGH);
  }
  else 
  {
    digitalWrite(RelayPin, LOW);
  }
}

void PIDsetup(int x, int WindowSize)
{
  //initialize the variables we're linked to
  Setpoint = x;

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC); 
}

