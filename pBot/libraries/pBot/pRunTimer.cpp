#include <pRunTimer.h>

RunTimer::RunTimer():TimerRoot()
{ }

RunTimer::RunTimer(TimerOwner* owner):TimerRoot(owner)
{ }

RunTimer::RunTimer(voidFunction externFunction):TimerRoot(externFunction)
{ }

boolean RunTimer::run()
{
  if(!timer_on) return false;
  if(getTime()<nextTimerEvent) return false;

  nextTimerEvent = getTime()+lapse;
  trigEvent();

  return true;
}

ulong RunTimer::getTime()
{
  if(use_micros)
      return micros();
  else
      return millis();
}

void RunTimer::startMicros(ulong microseconds)
{
  use_micros= true;
  start(microseconds);
}

void RunTimer::startMillis(ulong milliseconds)
{
  use_micros= false;
  start(milliseconds);
}

void RunTimer::start(ulong time)
{
  timer_on= true;
  lapse= time;
  nextTimerEvent= getTime()+lapse;
}

void RunTimer::stop() 
{ 
  timer_on= false; 
}

boolean RunTimer::timerIsOn()
{ 
  return timer_on; 
}

