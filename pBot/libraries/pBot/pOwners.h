// ---------------------------------------------------------------------------
// pBot Library - v1.0 - 12/03/2019
//
// AUTHOR/LICENSE:
// Created by Francesco A. Perrotti - faperrotti@hotmail.com
// Copyright 2014-2019 License: GNU General Public License v3
// http://www.gnu.org/licenses/
//
// Get the last version of this lib at:
// https://sourceforge.net/projects/arduino-libs/files
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

#ifndef pOwners_h
#define pOwners_h

#include "pGlobals.h"

// pOwners.h: abstract classes to receive events

// Stepper motor
//
class StpSingleOwner
{
public:
  virtual void onMoveDone(byte motorID, long steps){}
  virtual void onStepsDone(byte motorID, long steps, long totalSteps){}
};

// Buttons
//
class ButtonOwner{
public:
  	virtual void buttonPressed(byte btID){}
  	virtual void buttonReleased(byte btID){}
};

// Hcsr04
//
class HcsrOwner
{
public:
  virtual void onHcsrRead(byte hcID, int dist){}
};

// Timer
//
class TimerOwner
{
public:
  	virtual void onTimerEvent(){}
};

class TimerRoot: public TimerOwner
{
public:
	TimerRoot(){ }
 	TimerRoot(TimerOwner* owner){ this->owner= owner; }
 	TimerRoot(voidFunction externFunction){ externFunc= externFunction; }

 	void trigEvent()
 	{
 		if(owner) owner->onTimerEvent();
 		else
   		if(externFunc) externFunc();
   		else
     			onTimerEvent();
 	}

private:
  	TimerOwner* owner= NULL;
  	voidFunction externFunc= NULL;
};

#endif

