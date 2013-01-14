#include <PID_v1.h>

int thermo = A1;

void setup()
{
  pinMode(thermo, INPUT);
  //analogReference(DEFAULT);
  Serial.begin(9600);
}

void loop()
{
  int thermoVal = analogRead(thermo);
  Serial.println(thermoVal);
  delay(500);
}
