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

#ifndef pGlobals_h
#define pGlobals_h

#include <Arduino.h>

//
// pGlobals.h
//
// Some util definitions, types and functions
//

typedef unsigned int uint;
typedef unsigned long ulong;
typedef void (*voidFunction)();

#define sprint(a)    	 Serial.print(a)
#define sprint2(a, b)    {sprint(a); sprint(b);}
#define sprint3(a, b, c) {sprint2(a, b); sprint(c);}
#define sprint2d(caption, v1, v2, sufix) {sprint3(caption, "(", v1); sprint3(",", v2, ")"); sprint(sufix);}


#define circularInc(count, limit)  count= ((count+1) % limit)
#define circularDec(count, limit)  count= ((count+limit-1) % limit)
#define circularNext(count, limit) ((count+1) % limit)
#define circularPrev(count, limit) ((count+limit-1) % limit)


int freeRam();
float fmap(long x, long in_min, long in_max, float out_min, float out_max);
boolean inRange(float value, float in_min, float in_max);

// Move types
#define mv_Off       0
#define mv_Ahead     1
#define mv_Back      2
#define mv_Brake     3
#define mv_SpinLf    4
#define mv_SpinRg    5
#define mv_TurnLf    6
#define mv_TurnRg    7
#define mv_TurnBkLf  8
#define mv_TurnBkRg  9
#define mv_CurveLf   10
#define mv_CurveRg   11
#define mv_Moves     12


//#define MOTOR_MOVE_DEBUG

#ifdef MOTOR_MOVE_DEBUG
	extern const char strMove[mv_Moves][10];
#endif

#endif
