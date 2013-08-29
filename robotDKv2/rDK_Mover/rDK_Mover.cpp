/*
 * rDK_Mover.cpp
 *
 *  Created on: 21/04/2013
 *      Author: jcruz
 */

#include <Arduino.h>
#include <rDK_MotoresDC.h>
#include "rDK_Mover.h"

/***** Global Defines ****/

// defines for locations of sensors
const int SENSE_IR_LEFT  = 0;
const int SENSE_IR_RIGHT = 1;

// defines for directions
const int DIR_LEFT   = 0;
const int DIR_RIGHT  = 1;
const int DIR_CENTER = 2;

const char* locationString[] = {"Left", "Right", "Center"}; // labels for debug
// see http://arduino.cc/en/Reference/String for more on character string arrays

// obstacles constants
const int OBST_NONE       = 0;  // no obstacle detected
const int OBST_LEFT_EDGE  = 1;  // left edge detected
const int OBST_RIGHT_EDGE = 2;  // right edge detected
const int OBST_FRONT_EDGE = 3;  // edge detect at both left & right sensors

const int LED_PIN = 13;

/// move states:
enum        {MOV_LEFT, MOV_RIGHT, MOV_FORWARD, MOV_BACK, MOV_ROTATE, MOV_STOP};
const char* states[] = {"Left", "Right", "Forward", "Back", "Rotate", "Stop"};
/**** End of Global Defines ****************/

/*************************************
 Drive: mid level movement functions
*************************************/

int moveState = MOV_STOP;   // what robot is doing

int  moveSpeed   = 0;     // move speed stored here (0-100%)
int  speedIncrement = 10; // percent to increase or decrease speed



// this is the low level movement state.
// it will differ from the command state when the robot is avoiding obstacles
void changeMoveState(int newState)
{
  if(newState != moveState)
  {
    //Serial.print("Changing move state from "); Serial.print( states[moveState]);
    //Serial.print(" to "); Serial.println(states[newState]);
    moveState = newState;
  }
}

void moveStop()
{
  changeMoveState(MOV_STOP);
  motorStop(MOTOR_LEFT);
  motorStop(MOTOR_RIGHT);
}

void moveBrake()
{
  changeMoveState(MOV_STOP);
  motorBrake(MOTOR_LEFT);
  motorBrake(MOTOR_RIGHT);
}

void moveSetSpeed(int speed)
{
  motorSetSpeed(MOTOR_LEFT, speed) ;
  motorSetSpeed(MOTOR_RIGHT, speed) ;
  moveSpeed = speed; // save the value
}

void moveSlower(int decrement)
{
   //Serial.print(" Slower: ");
   if( moveSpeed >= speedIncrement + MIN_SPEED)
     moveSpeed -= speedIncrement;
   else moveSpeed = MIN_SPEED;
   moveSetSpeed(moveSpeed);
}


void moveFaster(int increment)
{
  //Serial.print(" Faster: ");
  moveSpeed += speedIncrement;
  if(moveSpeed > 100)
     moveSpeed = 100;
  moveSetSpeed(moveSpeed);
}

int moveGetState()
{
 return moveState;
}

void moveBegin()
{
   motorBegin(MOTOR_LEFT);
   motorBegin(MOTOR_RIGHT);
   moveStop();
}

void moveLeft()
{
  changeMoveState(MOV_LEFT);
  motorForward(MOTOR_LEFT,  0);
  motorForward(MOTOR_RIGHT, moveSpeed);
}

void moveRight()
{
  changeMoveState(MOV_RIGHT);
  motorForward(MOTOR_LEFT,  moveSpeed);
  motorForward(MOTOR_RIGHT, 0);
}

void moveForward()
{
  changeMoveState(MOV_FORWARD);
  motorForward(MOTOR_LEFT,  moveSpeed);
  motorForward(MOTOR_RIGHT, moveSpeed);
}

void moveBackward()
{
  changeMoveState(MOV_BACK);
  motorReverse(MOTOR_LEFT, moveSpeed);
  motorReverse(MOTOR_RIGHT, moveSpeed);
}


// function to check if robot can continue moving when taking evasive action
// returns true if robot is not blocked when moving to avoid obstacles
// this 'placeholder' version always returns true
boolean checkMovement()
{
  return true;
}

// check for obstacles while delaying the given duration in ms
void movingDelay(long duration)
{
  long startTime = millis();
  while(millis() - startTime < duration) {
     // function in Look module checks for obstacle in direction of movement
     if(checkMovement() == false) {
        if( moveState != MOV_ROTATE) // rotate is only valid movement
        {
            //Serial.println("Stopping in moving Delay()");
            moveBrake();
        }
     }
  }
}




/************* high level movement functions ****************/

//moves in the given direction at the current speed for the given duration in milliseconds
void timedMove(int direction, int duration)
{
  //Serial.print("Timed move ");
  if(direction == MOV_FORWARD) {
    //Serial.println("forward");
    moveForward();
  }
  else if(direction == MOV_BACK) {
    //Serial.println("back");
    moveBackward();
  }
  //else
    //Serial.println("?");

  movingDelay(duration);
  moveStop();
}



/*************************************
 functions to rotate the robot
*************************************/

// return the time in milliseconds to turn the given angle at the given speed
long rotationAngleToTime( int angle, int speed)
{
int fullRotationTime; // time to rotate 360 degrees at given speed

  if(speed < MIN_SPEED)
    return 0; // ignore speeds slower then the first table entry

  angle = abs(angle);

  if(speed >= 100)
    fullRotationTime = rotationTime[NBR_SPEEDS-1]; // the last entry is 100%
  else
 {
    int index = (speed - MIN_SPEED) / SPEED_TABLE_INTERVAL ; // index into speed and time tables
    int t0 =  rotationTime[index];
    int t1 = rotationTime[index+1];    // time of the next higher speed
    fullRotationTime = map(speed,  speedTable[index],  speedTable[index+1], t0, t1);
   // Serial.print("index= ");  Serial.print(index); Serial.print(", t0 = ");  Serial.print(t0);  Serial.print(", t1 = ");  Serial.print(t1);
 }
 // Serial.print(" full rotation time = ");  Serial.println(fullRotationTime);
  long result = map(angle, 0,360, 0, fullRotationTime);
  return result;
}


// rotate the robot from MIN_SPEED to 100% increasing by SPEED_TABLE_INTERVAL
void calibrateRotationRate(int direction, int angle)
{
  //Serial.print(locationString[direction]);
  //Serial.println(" calibration" );
  for(int speed = MIN_SPEED; speed <= 100; speed += SPEED_TABLE_INTERVAL)
  {

    delay(1000);
    //blinkNumber(speed/10);

    if( direction == DIR_LEFT)
    {    // rotate left
      motorReverse(MOTOR_LEFT,  speed);
      motorForward(MOTOR_RIGHT, speed);
    }
    else if( direction == DIR_RIGHT)
    {    // rotate right
      motorForward(MOTOR_LEFT,  speed);
      motorReverse(MOTOR_RIGHT, speed);
    }
    //else
    //   Serial.println("Invalid direction");


    int time = rotationAngleToTime(angle, speed);

//    Serial.print(locationString[direction]);
//    Serial.print(": rotate ");
//    Serial.print(angle);
//    Serial.print(" degrees at speed ");
//    Serial.print(speed);
//    Serial.print(" for ");
//    Serial.print(time);
//    Serial.println("ms");
    delay(time);
    motorStop(MOTOR_LEFT);
    motorStop(MOTOR_RIGHT);
    delay(2000); // two second delay between speeds
  }
}

void moveRotate(int angle)
{
  changeMoveState(MOV_ROTATE);
  //Serial.print("Rotating ");  Serial.println(angle);
  if(angle < 0)
  {
    //Serial.println(" (left)");
    motorReverse(MOTOR_LEFT,  moveSpeed);
    motorForward(MOTOR_RIGHT, moveSpeed);
    angle = -angle;
  }
  else if(angle > 0)
  {
    //Serial.println(" (right)");
    motorForward(MOTOR_LEFT,  moveSpeed);
    motorReverse(MOTOR_RIGHT, moveSpeed);
  }
  int ms = rotationAngleToTime(angle, moveSpeed);
  movingDelay(ms);
  moveBrake();
}




