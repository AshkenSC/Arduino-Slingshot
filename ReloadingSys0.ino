#include <Servo.h>

Servo servo1;  //Front barrier
Servo servo2;  //Second barrier
const int photo = A0;
int light;

int Reload();

void setup()
{
 servo1.attach(9);
 servo2.attach(10); 
}

void loop()
{
  light = analogRead(photo);
  Reload();
}

int Reload ()
{
  if(light > 100)
  //No ammo, reloading failed
  {
    return 0;
  }
  servo1.write(70);  //Open barrier 1 and reload
  delay(2000);
  
  //Reloading complete, start to reload the ball
  //into the reloading area
  servo1.write(0);  //Cloase barrier 1
  delay(1000);
  servo2.write(70);  //Open barrier 2
  delay(1000);
  
  //There is a ball in the reloading area
  servo2.write(0);   //Close barrier 2
  return 1;          //Reload succeed;
  
}
 
