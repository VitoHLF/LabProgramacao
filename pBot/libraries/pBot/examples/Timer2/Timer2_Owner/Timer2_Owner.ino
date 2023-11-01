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

// Example of Timer2 class usage.

#include <pTimer2.h>

/**
 * In this example a TimerOwner descending class is created.
 * TimerOwner is an abstract class that declares only the virtual 
 * method onTimerEvent().
 *
 * The Timer2 constructor receives by parameter a reference to the
 * instance created (tmo). This allows the Timer2 class to call the
 * onTimerEvent() method when needed. The instance of Timer2 is external 
 * to the class that executes the code associated with the timer event.
 */


class Timer2Owner: public TimerOwner
{
public:
  
  void begin()
  {
    pinMode(LED_BUILTIN, OUTPUT);
  }
  
  void onTimerEvent()
  {
    static boolean ledStatus= false;
    ledStatus= !ledStatus;
    digitalWrite(LED_BUILTIN, ledStatus);
  }
};

 
Timer2Owner tmo;
Timer2 tm2(&tmo);

void setup()
{
  tmo.begin();
  tm2.startMillis(350);
}

void loop()
{
  
}

