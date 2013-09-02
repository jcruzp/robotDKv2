// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef robotDKv2_H_
#define robotDKv2_H_
#include "Arduino.h"
//add your includes for the project robotDKv2 here
#include <Wii.h>
#include <Servo.h>
#include <rDK_Mover.h>

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project robotDKv2 here

USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
WII Wii(&Btd,PAIR); // This will start an inquiry and then pair with your Wiimote - you only have to do this once
//WII Wii(&Btd); // After that you can simply create the instance like so and then press any button on the Wiimote


Servo pan;
Servo tilt;
long currentX=0;
long currentY=0;

bool printAngle;

//Mueve la camera atada al mecanismo de Pan/Tilt
void MoverCamera(double roll, double pitch)
{
	currentX = map((long)roll, 0, 350, 0, 180);
	currentY = map((long)pitch, 0, 350, 180, 0);
	pan.write(currentX);
	tilt.write(currentY);
}

//Do not add code below this line
#endif /* robotDKv2_H_ */
