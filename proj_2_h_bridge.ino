#include "Arduino.h" // for eclipse

// pins
const int motor_right_pin = 13;
const int motor_left_pin = 12;
const int button_confirm_pin = 2;

int state_button_confirm = 0;

//The setup function is called once at startup of the sketch
void setup()
{
  pinMode(motor_left_pin, OUTPUT);
  pinMode(motor_right_pin, OUTPUT);

  pinMode(button_confirm_pin, INPUT);

  Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
  if(digitalRead(button_confirm_pin) == LOW)
  {
    digitalWrite(motor_left_pin, HIGH);
    Serial.println("MOTOR ON");
  }

  Serial.println("..");
  digitalWrite(motor_left_pin, LOW);
  digitalWrite(motor_right_pin, LOW);
}


