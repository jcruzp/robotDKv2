/*
 * rDK_Move.h
 *
 *  Created on: 21/04/2013
 *      Author: jcruz
 */

#ifndef RDK_MOVE_H_
#define RDK_MOVE_H_

void moveStop();
void moveBrake();
void moveSetSpeed(int speed);
void moveSlower(int decrement);
void moveFaster(int increment);
int moveGetState();
void moveBegin();
void moveLeft();
void moveRight();
void moveForward();
void moveBackward();
void movingDelay(long duration);
void timedMove(int direction, int duration);
long rotationAngleToTime( int angle, int speed);
void calibrateRotationRate(int direction, int angle);
void moveRotate(int angle);

#endif /* RDK_MOVE_H_ */
