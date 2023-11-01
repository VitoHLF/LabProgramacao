#include "pBattSense.h"

/////////////////////////////////////////////////////////////////////////
///
/// BatterySense
///

/*

  float lastVin;
  boolean battHalf= false;
  boolean battLow = false;

  BatterySense(){}
  void begin(
  float readVIn();
  void run();

protected:
  float constVin;
  int minVal, halfVal;
	byte sensePin, ledPin;

	constVin= 59.6382

	16.14   4.7   10.8
*/

void BatterySense::begin(float maxVin, float maxVout, float minVin, byte sensePin, byte ledPin, float vOutRef)
{
	constVin= (maxVout*1023/vOutRef)/maxVin;
	lowVal= round(minVin * constVin);
	halfVal= round(((maxVin+minVin)/2) * constVin);

	this->sensePin= sensePin;
	this->ledPin= ledPin;

  	pinMode(sensePin, INPUT);
	if(ledPin != BS_NO_BATT_LED)
	{
	  	pinMode(ledPin, OUTPUT);
	}
}

float BatterySense::readVIn()
{
	int rVal= analogRead(sensePin);
	delayMicroseconds(3);
	rVal= (rVal + analogRead(sensePin)) / 2;

	battHalf= rVal <= halfVal;
	battLow= rVal <= lowVal;
	lastVin= rVal / constVin;

   return lastVin;
}

void BatterySense::run()
{
	readVIn();
	if(ledPin == BS_NO_BATT_LED) return;

   unsigned long mil= millis();

	if(battLow)
	 digitalWrite(ledPin, !(((mil>>8) | (mil>>6))&1));
	else
	  if(battHalf)
	    digitalWrite(ledPin, (mil>>8)&1);
     else  
     	 digitalWrite(ledPin, ((mil>>10)&(mil>>9)&(mil>>8)&(mil>>7)&(mil>>6))&1);
}

