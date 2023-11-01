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

#ifndef pRunTimer_h
#define pRunTimer_h
#include "pGlobals.h"
#include "pOwners.h"

/////////////////////////////////////////////////////////////
// Classe RunTimer
//
// Emula um timer via software, sem usar os timers de hardware 
// do arduíno.
// 

class RunTimer: private TimerRoot
{
public:
  RunTimer();
  RunTimer(TimerOwner* owner);
  RunTimer(voidFunction externFunction);

  void startMicros(ulong microseconds);
  void startMillis(ulong milliseconds);
  void stop();

  boolean run();
  boolean timerIsOn();

// de TimerOwner:
// virtual void onTimerEvent(){}
// de TimerRoot: 
// void trigEvent();
private:
  boolean use_micros= false;
  boolean timer_on= false;
  ulong nextTimerEvent;
  ulong lapse;
  ulong getTime();
  void start(ulong time);
};

#endif
