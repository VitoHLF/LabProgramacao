pBot Arduino library

Check wiki for more details:
https://sourceforge.net/p/arduino-libs/wiki/


pGlobals.h: Some util definitions, types and functions.

pCircBuff.h: Implements a circular buffer class
	class CircularBuffer

pHcsr04.h: Classes to drive Hcsr-04 ultrasonic distance sensor
	class Hcsr04
	class HcsrAuto
	class HcsrArray

pRunTimer.h: Simple software timer. 
	class RunTimer

pTimer2.h: Provide easy access to Timer2 hardware timer of arduino
	class Timer2

pBattSense.h: Class to drive a simple battery level sensor. 
              To use this class you need to do the circuit describe 
              in pBattSense.png. Includes a warning led.
	class BatterySense

pBattSense.png:	Battery sensor electrical schematic
			
pPushButton.h: Classes to drive a push button and push button array
	class PushButton
	class PushButtonArray

pJoystick.h: driver to joystick module

pRadioMsg.h: Driver to nRF24L01 radio transceiver. 
             Encapsule RF24 class (J. Coliz lib) and implement a basic message 
             format to communication. Take care of communication details.
	class RadioMessage

pJoyStickV1a.h: Driver to Joystick Shield V1.a board.
                Generate events from buttons and joystick moves.
	class JoyStickShield

pJsRadio.h: Driver to Joystick Shield V1.a board whith RF24 radio conected.
	class JsRadioMaster
	class JsRadioSlave

pDcMotors.h: Class to drive a dc motor's pair to move robots.
	class DcMotorCouple


pStpMotor.h: Class to control a single stepper motor. This class is mean to be used
	     by StepperCouple class.
	class StepperSingle

pStpCouple.h: Class to control a pair of stepper motors to produce 11 diferent movements. 
	      Implements automatic acceleration and deceleratios features, can use (or not) 
	      timer2 arduino's timer to temporize steps, store and execute movements sequences, 
	      movements can be informed in centimeters or degrees.
	class StepperCouple
		
	      
