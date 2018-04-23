#include "Arduino.h" // for eclipse

// Analog
const int pin_microphone = 0;

//The setup function is called once at startup of the sketch
void setup()
{
  pinMode(pin_microphone, INPUT);

  Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
  int val_microphone = analogRead(pin_microphone);

//  Serial.print("test");
  if(val_microphone > 700)
      Serial.println(val_microphone);

}


