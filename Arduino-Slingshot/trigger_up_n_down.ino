#include <Servo.h>

Servo trigger;

void triggerHold();
void triggerRelease();

void setup()
{
  trigger.attach(9);
  Serial.begin(9600);
}

void loop()
{
  triggerHold();
  Serial.println("hold");
  delay(4000);
  triggerRelease();
  Serial.println("Release");
  delay(4000);
}

void triggerHold()
{
 trigger.write(120); 
}

void triggerRelease()
{
  trigger.write(30);                                             
}
