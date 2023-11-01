// ---------------------------------------------------------------------------
// pBot Library - v1.05 - 10/03/2019
//
// AUTHOR/LICENSE:
// Created by Francesco A. Perrotti - faperrotti@hotmail.com
// Copyright 2014 License: GNU General Public License v3
// http://www.gnu.org/licenses/
//
// Download
// https://sourceforge.net/projects/arduino-libs/files/
//
// DISCLAIMER:
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
// ---------------------------------------------------------------------------
//
// Esta biblioteca é parte do projeto de desenvolvimento de robôs móveis 
// desenvolvido por Francesco A. Perrotti para a Fatec Americana.
// Pode ser usada para fins comerciais ou pessoais livremente,
// apenas deixe citado o autor.
//

#ifndef pDcMotors_h
#define pDcMotors_h

#include "pGlobals.h"

//////////////////////////////////////////////
// SingleDcMotor
//

#define DC_BLINK_LAPSE 	16
#define DC_BRAKE_TIME	255
#define DC_NO_ENB_PIN	255

class SingleDcMotor
{
public:
	boolean moving = false;
	byte mvType;
	boolean useEnable= false;

	// boolean isLf= true;   // for debug

	SingleDcMotor(){};
	void begin(byte aheadPin, byte backPin, byte enablePin= DC_NO_ENB_PIN);
	void move(byte bitAhead, byte bitBack, int speed);
	void moveOff();
	void run();
	void setSpeedRatio(float speedRatio);

private:
	byte aheadPin, backPin, enablePin;		
	ulong nextBlink= 0;
	uint speedRatio= 1000;
	int lastAhead, lastBack, lastSpeed;
	boolean blink;

	void writeMove(byte bitAhead, byte bitBack, int speed);
	void motorSwitch(boolean turnOn);
};

//////////////////////////////////////////////
// DcMotorCouple
//

class DcMotorCouple
{
public:
	byte mvType;
	int lastSpeed;

	DcMotorCouple();
	void begin();
	void beginLf(byte lfAheadPin, byte lfBackPin, byte lfEnablePin= DC_NO_ENB_PIN);
	void beginRg(byte rgAheadPin, byte rgBackPin, byte rgEnablePin= DC_NO_ENB_PIN);

	void move(byte mvType, int speed, ulong milliseconds=0);

	void moveOff();
	void stopNow(int milliseconds= DC_BRAKE_TIME);

	void run();
	boolean isMoving();

	void setSpeedRatio(float lfRatio, float rgRatio);
	void updateSpeed(int speed);
	void updateSpeed();

private:
	SingleDcMotor *lf, *rg;
	ulong timeOff= 0;
};

#endif