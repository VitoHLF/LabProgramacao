#include "pHcsr04.h"

Hcsr04::Hcsr04()
{

}

#define cmtConst 0.01717           // Centimeter constant at 20° celsius
#define inchConst (cmtConst/2.54)  // Inch constant at 20° celsius

void Hcsr04::begin(byte triggerPin, byte echoPin, DistUnit unit)
{
  this->triggerPin= triggerPin;
  this->echoPin   = echoPin;
  this->unit= unit;
  
  if(triggerPin!=echoPin)
  {
    pinMode(triggerPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
  }
}

long Hcsr04::ultraSonicRead()
{   
  if(triggerPin==echoPin)
    pinMode(triggerPin, OUTPUT);  

  digitalWrite(triggerPin, LOW);   delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);   

  if(triggerPin==echoPin)
    pinMode(echoPin, INPUT);  

  long int
    itime= micros() + hc_TimeOut;
  
  while (!digitalRead(echoPin))
    if(micros()>=itime) return hcErr_Hardware;
    
  itime= micros();
  while (digitalRead(echoPin))
    if(micros()-itime >= hc_TimeOut) return hcErr_Timeout;
    
  return micros()- itime;

//  return pulseIn(echoPin, HIGH, hc_TimeOut);
//  pulseIn() function interferes with radio operation
}

int Hcsr04::hcDist(byte tries)
{   
  if(!tries) tries= 1;

  long tm;
  while(tries)
  {
    tm= ultraSonicRead();
    if(tm >= 0) break;
    tries--;
  }
  float distConst= unit? inchConst: cmtConst;
  return tm>=0?round(tm*distConst):tm;
}

/////////////////////////////////////////////////////////////////////
///
/// HcsrAuto
///

void HcsrAuto::begin(byte triggerPin, byte echoPin, DistUnit unit)
{
  Hcsr04::begin(triggerPin, echoPin, unit);
}

void HcsrAuto::hcStart(uint milliseconds)
{
  lapse= milliseconds;
  nextRead= millis()+lapse;
}

void HcsrAuto::hcStop()
{
  lapse= 0;
}

//int HcsrAuto::readNow(byte tries)
//{
//  lastDist= hcDist(tries);
//  onHcRead(lastDist);
//  return lastDist;
//}

boolean HcsrAuto::run()
{
  if(lapse && nextRead<=millis())
  {
    lastDist= hcDist();
    onHcRead(lastDist);
    nextRead+= lapse;
    return true;
  }
  return false;
}

/////////////////////////////////////////////////////////////////////
///
/// HcsrArray
///

HcsrArray::~HcsrArray()
{
  if(hc) 
  {
    free(hc);
  }
}


boolean HcsrArray::begin(byte maxSensors, DistUnit unit)
{
  count = 0;
  nextRead= 0;
  patrolCount= 0;
  lapse= hc_PatrolLapse;
  this->unit= unit;

  this->maxSensors= maxSensors;
  hc= (HcsrItem**)malloc(maxSensors*sizeof(HcsrItem*));
  return hc != NULL;
}

int HcsrArray::addHcSensor(byte triggerPin, byte echoPin)
{
  if (count >= maxSensors) return hcErr_ArrayIsFull;

  hc[count] = new HcsrItem();
  if(!hc[count]) return hcErr_NoMemory;

  hc[count]->begin(triggerPin, echoPin, unit);
  count++;
  return count-1;
}

void HcsrArray::patrolModeOn(uint milliseconds) 
{ 
  patrol_on= true;
  patrolCount= 0;
  lapse= milliseconds;
  nextRead= millis();
}

void HcsrArray::patrolModeOff()
{ 
  patrol_on= false;
}

int HcsrArray::readHcDist(byte hcID, byte tries)
{
  return lastDist= hc[hcID]->readNow(tries);
}

int HcsrArray::readHcArray(byte tries)
{
  int ct=0;
  for(int i=0; i<count; i++)
  {
    readHcDist(i, tries);
    if(lastDist>0) ct++;
  }
  return ct;
}

boolean HcsrArray::run()
{
  patrol_done= false;
  if(patrol_on && (nextRead<=millis()))
  {
    nextRead= millis()+lapse;
    lastHc= patrolCount;
    readHcDist(lastHc);
    onNextHcRead(lastHc, lastDist);

    circularInc(patrolCount, count);
    if(!patrolCount)
    {
      patrol_done= true;
      onPatrolDone();
    }
    return true;
  }
  return false;
}

int HcsrArray::getMinDist()
{
  int minDist= 32000;
  for(int i=0; i<count; i++)
  {
    if(hc[i]->lastDist<0) continue;

    if(hc[i]->lastDist<minDist)
    {
      minDist= hc[i]->lastDist;
      lastHc= i;
    }
  }
  return minDist;
}

int HcsrArray::getMaxDist()
{
  int maxDist= 0;
  for(int i=0; i<count; i++)
  {
    if(hc[i]->lastDist > maxDist)
    {
      maxDist= hc[i]->lastDist;
      lastHc= i;
    }
  }
  return maxDist;
}
  
byte HcsrArray::lastHcID()
{
  return lastHc;
}

int HcsrArray::getLastDist()
{
  return lastDist;
}

int HcsrArray::getLastDist(byte hcID)
{ 
  return hc[hcID]->lastDist; 
}
