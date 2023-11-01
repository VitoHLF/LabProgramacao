#include "pGlobals.h"

#ifdef MOTOR_MOVE_DEBUG
	const char strMove[mv_Moves][10]={
		"Off",
		"Ahead",
		"Back",
		"Brake",
		"SpinLf",
		"SpinRg",
		"TurnLf",
		"TurnRg",
		"TurnBkLf",
		"TurnBkRg",
		"CurveLf",
		"CurveRg"
	};
#endif

int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval==0? (int)&__heap_start: (int)__brkval);
}

float fmap(long x, long in_min, long in_max, float out_min, float out_max)
{
  return (x-in_min)* (out_max-out_min)/ (in_max-in_min) +out_min;
}

boolean inRange(float value, float in_min, float out_max)
{
	return (value>=in_min) && (value<out_max);
}
