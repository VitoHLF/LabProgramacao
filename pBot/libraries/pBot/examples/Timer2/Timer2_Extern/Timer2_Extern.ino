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
 * In this example an external function is created to execute the code
 * associated with timer events. This function must be informed
 * in the Timer2 constructor and will be called to each event automatically. 
 */

void timerEvent()
{
  static boolean ledStatus= false;
  ledStatus= !ledStatus;
  digitalWrite(LED_BUILTIN, ledStatus);
}


Timer2 tm2(timerEvent);
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  tm2.startMillis(400);  
}

void loop() 
{

}

