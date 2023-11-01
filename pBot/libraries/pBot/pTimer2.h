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

/*
	Adaptado por Francesco Artur Perrotti em 2016

	Original code from the Tone Library by Brett Hagman

	Adapted and Optimized by WilliamK @ Wusik Dot Com (c) 2010
	http://arduino.wusik.com

	Compact 8 Bit Timer (uses Timer2)

	Min frequency for Start() = 62 hz at 16 Mhz clock or 32 hz at 8 Mhz clock
	Max frequency for Start() = 16 Mhz at 16 Mhz clock or 8 Mhz at 8 Mhz clock
*/

#ifndef pTimer2_h
#define pTimer2_h

#include "pGlobals.h"
#include "pOwners.h"

// ------------------------------------------------------------------------------------------- //
class Timer2: public TimerRoot
{
public:
	Timer2();
  	Timer2(TimerOwner* owner);
  	Timer2(voidFunction externFunction);
	~Timer2();

	void startMicros(ulong microseconds);
	void startMillis(ulong milliseconds);

	void stop();
	ulong overlaps();

  	virtual void onTimerEvent(){}

private:
	void startF(float frequency);
};

#endif

