#include "pDcMotors.h"

typedef struct 
{
	boolean la, lb, ra, rb;	
}
TDcMovePins;

TDcMovePins mvPins[mv_Moves]= {
  {0, 0, 0, 0}, //   0 - engines off
  {1, 0, 1, 0}, //   1 - ahead
  {0, 1, 0, 1}, //   2 - back
  {1, 1, 1, 1}, //   3 - brake
  {0, 1, 1, 0}, //   4 - spinLf
  {1, 0, 0, 1}, //   5 - spinRg
  {1, 1, 1, 0}, //   6 - turnLf
  {1, 0, 1, 1}, //   7 - turnRg
  {1, 1, 0, 1}, //   8 - turnBkLf
  {0, 1, 1, 1}, //   9 - turnBkRg
  {1, 0, 1, 0}, //   10- curveLf
  {1, 0, 1, 0}  //   11- curveRg
};

/////////////////////////////////////////////////////////////////////////
///
/// SingleDcMotor
///

void SingleDcMotor::begin(byte aheadPin, byte backPin, byte enablePin)
{
	this->aheadPin= aheadPin;
	this->backPin= backPin;
	pinMode(aheadPin, OUTPUT);
	pinMode(backPin, OUTPUT);

	this->enablePin= enablePin;
	useEnable= enablePin!=DC_NO_ENB_PIN;
	if(useEnable)
		pinMode(enablePin, OUTPUT);

	moveOff();
}

void SingleDcMotor::moveOff()
{
	writeMove(0, 0, 0);
	moving = false;
	nextBlink= 0;
}

void SingleDcMotor::motorSwitch(boolean turnOn)
{
	if(turnOn)
	{
		if(useEnable) analogWrite(enablePin, lastSpeed);
		else{
		   analogWrite(aheadPin, lastAhead);
		   analogWrite(backPin , lastBack);
		}
	}
	else{
		if(useEnable) analogWrite(enablePin, 0);
		else{
		   analogWrite(aheadPin, 0);
		   analogWrite(backPin, 0);
		}
	}
}

void SingleDcMotor::setSpeedRatio(float speedRatio)
{
	this->speedRatio= (uint)(speedRatio*1000);
}

void SingleDcMotor::writeMove(byte bitAhead, byte bitBack, int speed)
{
//	if(isLf) sprint("writeMove  ");
	if(useEnable)
	{
		lastAhead= bitAhead;
		lastBack = bitBack;
		lastSpeed= max(0, min(255, ((long)speed*speedRatio)/1000));

	   digitalWrite(aheadPin, bitAhead);
	   digitalWrite(backPin , bitBack);
		analogWrite(enablePin, lastSpeed);
  		
//  		sprint2d(lastSpeed, bitAhead, bitBack, " \t");
	}
	else{
		lastSpeed= speed;
		lastAhead= max(0, min(255, ((long)bitAhead*speed*speedRatio)/1000));
		lastBack = max(0, min(255, ((long)bitBack *speed*speedRatio)/1000));

	   analogWrite(aheadPin, lastAhead);
	   analogWrite(backPin , lastBack);
  		
//  		sprint2d(0, lastAhead, lastBack, " \t");
	}
   moving= bitAhead || bitBack;
//	if(!isLf) sprint("\n");
}

void SingleDcMotor::move(byte bitAhead, byte bitBack, int speed)
{
	writeMove(bitAhead, bitBack, speed);

	if(bitAhead && bitBack)
	{
		nextBlink= millis()+DC_BLINK_LAPSE;
		blink= true;
	}
	else
		nextBlink= 0;
}

void SingleDcMotor::run()
{
	if(nextBlink && nextBlink<=millis())
	{
		blink= !blink;
		motorSwitch(blink);
		nextBlink= millis()+DC_BLINK_LAPSE;
	}
}


/////////////////////////////////////////////////////////////////////////
///
/// DcMotorCouple
///

DcMotorCouple::DcMotorCouple()
{
	lf= new SingleDcMotor();   
	rg= new SingleDcMotor();	
}

void DcMotorCouple::begin()
{
}

void DcMotorCouple::beginLf(byte lfAheadPin, byte lfBackPin, byte lfEnablePin)
{
	lf->begin(lfAheadPin, lfBackPin, lfEnablePin);
}

void DcMotorCouple::beginRg(byte rgAheadPin, byte rgBackPin, byte rgEnablePin)
{
	rg->begin(rgAheadPin, rgBackPin, rgEnablePin);
}

void DcMotorCouple::setSpeedRatio(float lfRatio, float rgRatio)
{
	lf->setSpeedRatio(lfRatio);
	rg->setSpeedRatio(rgRatio);
}

void DcMotorCouple::moveOff()
{
	lf->moveOff();
	rg->moveOff();
	mvType= mv_Off;
	timeOff= 0;
}

void DcMotorCouple::stopNow(int milliseconds)
{
	move(mv_Brake, 240, milliseconds);
}


boolean DcMotorCouple::isMoving()
{
	return lf->moving || rg->moving;
}

void DcMotorCouple::move(byte mvType, int speed, ulong milliseconds)
{
	this->mvType= mvType;
	lastSpeed= speed;

	lf->move(mvPins[mvType].la, mvPins[mvType].lb, speed);
	rg->move(mvPins[mvType].ra, mvPins[mvType].rb, speed);

	if(milliseconds)
		timeOff= millis()+milliseconds;
	else
		timeOff= 0;
}

void DcMotorCouple::updateSpeed(int speed)
{
	move(mvType, speed);
}

void DcMotorCouple::updateSpeed()
{
	move(mvType, lastSpeed);
}

void DcMotorCouple::run()
{
	if(timeOff && timeOff<=millis())
		moveOff();

	lf->run();
	rg->run();
}
