#include "Arduino.h" // for eclipse
#include <Servo.h>

// digital pins
const int button_confirm_pin = 2;
const int servo_direction_pin = 3;
const int echo_pin = 5;   // Pin to receive echo pulse
const int trig_pin = 6;   // Pin to send trigger pulse
const int button_left_pin = 7;
const int button_right_pin =  8;
const int servo_reload_front_pin = 9;
const int servo_reload_back_pin = 10;
const int servo_trigger_pin = 11;
const int motor_left_pin = 12;
const int motor_right_pin = 13;


//// analog pins
const int microphone_pin = A0;
const int noise_threshold_potentiometer_pin = A1;
const int led_modify_direction = A2;
const int led_preparation = A3;
const int led_reload_empty = A4;
const int ldr_pin = A5;


// defines
#define OFF     0
#define ON      1
#define RIGHT   2
#define LEFT    3
#define PULL    LEFT    // TODO: Evaluate
#define RELEASE RIGHT   // TODO: Evaluate
#define SET_DIRECTION   0
#define PREPARATION     1
#define READY           2

// global variables
int state_button_right = 0;
int state_button_left = 0;
int state_button_confirm = 0;
int program_step = SET_DIRECTION;

int trigger_mode = OFF;

Servo trigger;


// don't touch variables
int Motor_status = OFF;

// Function prototypes
void motorOff();
void motorOn(int direction);
long getDistance();
int checkNoiseImpuls(int threshold);
void directionServo(int direction);
int checkConfirm();
int getPullDelay();
void triggerHold();
void triggerRelease();
int reload();

//The setup function is called once at startup of the sketch
void setup()
{
  pinMode(button_left_pin, INPUT);
  pinMode(button_right_pin, INPUT);
  pinMode(button_confirm_pin, INPUT);

  pinMode(led_modify_direction, OUTPUT);
  pinMode(led_preparation, OUTPUT);
  pinMode(led_reload_empty, OUTPUT);

  pinMode(motor_left_pin, OUTPUT);
  pinMode(motor_right_pin, OUTPUT);

  pinMode(servo_direction_pin, OUTPUT);
  pinMode(servo_reload_back_pin, OUTPUT);
  pinMode(servo_reload_front_pin, OUTPUT);
  pinMode(servo_trigger_pin, OUTPUT);

  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);

  pinMode(noise_threshold_potentiometer_pin, INPUT);
  pinMode(microphone_pin, INPUT);
  pinMode(ldr_pin, INPUT);

  trigger.attach(servo_trigger_pin);

  Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
  if(digitalRead(button_right_pin) == LOW)
  {
    Serial.println("MOTOR RELEASE");
    motorOn(RELEASE);
  }
  else if(digitalRead(button_left_pin) == LOW)
  {
    Serial.println("MOTOR PULL");
    motorOn(PULL);
  }
  else
  {
    motorOff();
  }


  if(checkConfirm() == 1 && trigger_mode == OFF)
  {
    Serial.println("TRIGGER HOLD");
    triggerHold();
    trigger_mode = ON;
    delay(500);
  }
  if(checkConfirm() == 1 && trigger_mode == ON)
  {
    Serial.println("TRIGGER RELEASE");
    triggerRelease();
    trigger_mode = OFF;
    delay(500);
  }
}

void triggerHold()
{
  trigger.write(130);
}

void triggerRelease()
{
  trigger.write(30);
}


/*
 * Stop motor
 */
void motorOff()
{
  digitalWrite(motor_right_pin, LOW);
  digitalWrite(motor_left_pin, LOW);
  Motor_status = OFF;
}

/*
 * Start motor
 * parameter direction: RIGHT or LEFT
 */
void motorOn(int direction)
{
//  Serial.println(Motor_status);

  if(direction == RIGHT)
  {
    switch(Motor_status)
    {
      case OFF:
        digitalWrite(motor_right_pin, HIGH);
        Motor_status = RIGHT;
        break;
      case LEFT:
        digitalWrite(motor_left_pin, LOW);
        delay(100);
        digitalWrite(motor_right_pin, HIGH);
        Motor_status = RIGHT;
        break;
      case RIGHT:
        Serial.println("[motorOn()] Motor is already turning right");
        break;
      default:
        Serial.println("[motorOn()] ERROR!!!! Motor_status wrong!!!!");
        break;
    }
  }
  else if(direction == LEFT)
  {
    switch(Motor_status)
    {
      case OFF:
        digitalWrite(motor_left_pin, HIGH);
        Motor_status = LEFT;
        break;
      case LEFT:
        Serial.println("[motorOn()] Motor is already turning left");
        break;
      case RIGHT:
        digitalWrite(motor_right_pin, LOW);
        delay(100);
        digitalWrite(motor_left_pin, HIGH);
        Motor_status = LEFT;
        break;
      default:
        Serial.println("[motorOn()] ERROR!!!! Motor_status wrong!!!!");
        break;
    }
  }
  else
  {
    Serial.println("[motorOn()] parameter 'direction' is wrong!");
  }
}

int checkConfirm()
{
  state_button_confirm = digitalRead(button_confirm_pin);

//  int noise_threshold = analogRead(noise_threshold_potentiometer_pin);
//  noise_threshold = map(noise_threshold, 0, 1023, 500, 900);

  if(state_button_confirm == LOW || checkNoiseImpuls(700))
    return 1;
  else
    return 0;
}

int checkNoiseImpuls(int threshold)
{
  int val_microphone = analogRead(microphone_pin);

  if(val_microphone > threshold)
  {
    Serial.println(val_microphone);
    return 1;
  }
  else
  {
    return 0;
  }

}
