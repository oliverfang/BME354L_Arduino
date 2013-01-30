#include <PID_v1.h>
//Type K is 40uV/C
int thermo = A1;
int thermoVal;
int fan = 7;
int counter = 0;

void setup()
{
  pinMode(thermo, INPUT);
  pinMode(fan, OUTPUT);
  //analogReference(DEFAULT);
  Serial.begin(9600);
}

void loop()
{
  int thermoVal = analogRead(thermo);
  Serial.println(thermoVal);
  delay(1000);
}
