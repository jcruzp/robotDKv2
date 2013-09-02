// Do not remove the include below
#include "robotDKv2.h"



//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	  if (Usb.Init() == -1) {
	    Serial.print(F("\r\nOSC did not start"));
	    while(1); //halt
	  }
	  pan.attach(10);
	  tilt.attach(9);
	  Serial.print(F("\r\nFinished setupn"));
	  Serial.print(F("\r\nWiimote Bluetooth Library Started"));
}

// The loop function is called in an endless loop
void loop()
{
	Usb.Task();
	  if(Wii.wiimoteConnected) {
	    if(Wii.getButtonClick(HOME)) { // You can use getButtonPress to see if the button is held down
	      Serial.print(F("\r\nHOME"));
	      Wii.disconnect();
	    }
	    else {
	      if(Wii.getButtonClick(LEFT)) {
	        Wii.setAllOff();
	        Wii.setLedOn(LED1);
	        Serial.print(F("\r\nLeft"));
	        moveLeft();
	      }
	      if(Wii.getButtonClick(RIGHT)) {
	        Wii.setAllOff();
	        Wii.setLedOn(LED3);
	        Serial.print(F("\r\nRight"));
	        moveRight();
	      }
	      if(Wii.getButtonClick(DOWN)) {
	        Wii.setAllOff();
	        Wii.setLedOn(LED4);
	        Serial.print(F("\r\nDown"));
	        moveBackward();
	      }
	      if(Wii.getButtonClick(UP)) {
	        Wii.setAllOff();
	        Wii.setLedOn(LED2);
	        Serial.print(F("\r\nUp"));
	        moveForward();
	      }

	      if(Wii.getButtonClick(PLUS))
	        Serial.print(F("\r\nPlus"));
	      if(Wii.getButtonClick(MINUS))
	        Serial.print(F("\r\nMinus"));

	      if(Wii.getButtonClick(ONE))
	        Serial.print(F("\r\nOne"));
	      if(Wii.getButtonClick(TWO))
	        Serial.print(F("\r\nTwo"));

	      if(Wii.getButtonClick(A)) {
	        printAngle = !printAngle;
	        Serial.print(F("\r\nA"));
	      }
	      if(Wii.getButtonClick(B)) {
	        Wii.setRumbleToggle();
	        Serial.print(F("\r\nB"));
	      }
	    }
	    if(printAngle) {
	      Serial.print(F("\r\nPitch: "));
	      Serial.print(Wii.getPitch());
	      Serial.print(F("\tRoll: "));
	      Serial.print(Wii.getRoll());




	      if(Wii.motionPlusConnected) {
	        Serial.print(F("\tYaw: "));
	        Serial.print(Wii.getYaw());
	      }
	      if(Wii.nunchuckConnected) {
	        Serial.print(F("\tNunchuck Pitch: "));
	        Serial.print(Wii.nunchuckPitch);
	        Serial.print(F("\tNunchuck Roll: "));
	        Serial.print(Wii.nunchuckRoll);
	        MoverCamera(Wii.nunchuckRoll,Wii.nunchuckPitch);
	      }
	    }


	    //delay(dtime);

	  }
	  if(Wii.nunchuckConnected) {
	    if(Wii.getButtonClick(Z))
	      Serial.print(F("\r\nZ"));
	    if(Wii.getButtonClick(C))
	      Serial.print(F("\r\nC"));
	    if(Wii.getAnalogHat(HatX) > 137 ||  Wii.getAnalogHat(HatX) < 117 || Wii.getAnalogHat(HatY) > 137 || Wii.getAnalogHat(HatY) < 117) {
	      Serial.print(F("\r\nHatX: "));
	      Serial.print(Wii.getAnalogHat(HatX));
	      Serial.print(F("\tHatY: "));
	      Serial.print(Wii.getAnalogHat(HatY));

	    }
	  }
}
