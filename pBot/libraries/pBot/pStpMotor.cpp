// ---------------------------------------------------------------------------
// pBot Library - v1.05 - 10/03/2019
//
// AUTHOR/LICENSE:
// Created by Francesco A. Perrotti - faperrotti@hotmail.com
// Copyright 2014 License: GNU General Public License v3
// http://www.gnu.org/licenses/
//
// Download
// https://sourceforge.net/projects/arduino-libs/files/
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

#include "pStpMotor.h"

char mPins[8] = 
{
  B0001,  // 0
  B0011,  // 1
  B0010,  // 2
  B0110,  // 3
  B0100,  // 4
  B1100,  // 5
  B1000,  // 6
  B1001   // 7
};


////////////////////////////////////////////////
/// Classe StepperSingle
///

StepperSingle::StepperSingle():StepperControl()
{

}

StepperSingle::StepperSingle(byte motorID, StpSingleOwner* owner)
              :StepperControl(motorID, owner)
{

}

void StepperSingle::begin(uint startSpeed, uint cruiseSpeed)
{
  StepperControl::begin(startSpeed, cruiseSpeed);
}

void StepperSingle::beginPins(int mPin1, int mPin2, int mPin3, int mPin4)
{
  StepperControl::beginPins(mPin1, mPin2, mPin3, mPin4);
}

void StepperSingle::setBrakeCutPercent(byte brakeCutPercent)
{
  StepperControl::setBrakeCutPercent(brakeCutPercent);
}

void StepperSingle::enableAutoRun()
{
  StepperControl::enableAutoRun();
}

void StepperSingle::turboOn()
{
  StepperControl::turboOn();
}

void StepperSingle::turboOff()
{
  StepperControl::turboOff();
}

void StepperSingle::halfStepOn()
{
  StepperControl::halfStepOn();
}

void StepperSingle::halfStepOff()
{
  StepperControl::halfStepOff();
}

boolean StepperSingle::halfStep()
{
  return StepperControl::halfStep();
}

void StepperSingle::motorOff()
{
  StepperControl::motorOff();
}

void StepperSingle::moveSteps(TStepDirection direction, long steps, float ratio, boolean oddOnly)
{
  StepperControl::moveSteps(direction, steps, ratio, oddOnly);
}

void StepperSingle::moveOn(TStepDirection direction, float ratio, boolean oddOnly)
{
  moveOn(direction, ratio, oddOnly);
}

void StepperSingle::run()
{
  StepperControl::run();
}

void StepperSingle::autoRun()
{
  StepperControl::autoRun(); 
}


void StepperSingle::stopNow()
{
  StepperControl::stopNow();
}

void StepperSingle::decelStop()
{
  StepperControl::decelStop();
}

boolean StepperSingle::isMoving()
{
  return StepperControl::isMoving();
}

long StepperSingle::getReportCount()
{
  return StepperControl::getReportCount();
}

void StepperSingle::clearReportCount()
{
  StepperControl::clearReportCount();
}



////////////////////////////////////////////////
/// Classe StepperBits
///

StepperBits::StepperBits()
{

}

void StepperBits::begin(int mPin1, int mPin2, int mPin3, int mPin4)
{
  this->mPin_1 = mPin1;
  this->mPin_2 = mPin2;
  this->mPin_3 = mPin3;
  this->mPin_4 = mPin4;

  pinMode(this->mPin_1, OUTPUT);
  pinMode(this->mPin_2, OUTPUT);
  pinMode(this->mPin_3, OUTPUT);
  pinMode(this->mPin_4, OUTPUT);

  // posiciona o rotor do motor
  motorPinsOut(1);
  delay(3);
  motorPinsOut(0);

  stepNumber = 0;      
  stepInc= 2;  // halfStepOff()
}

void StepperBits::motorOff()
{ 
  motorPinsOut(0); 
} 

void StepperBits::motorPinsOut(byte pins)
{
  digitalWrite(mPin_1, pins & 1);
  digitalWrite(mPin_2, (pins>>1) & 1);
  digitalWrite(mPin_3, (pins>>2) & 1);
  digitalWrite(mPin_4, (pins>>3) & 1);
}

byte StepperBits::doNextStep(TStepDirection direction)
{ 
  stepNumber = (stepNumber + 8 + direction*stepInc) % 8;
  byte pins= mPins[stepNumber];
  motorPinsOut(pins);
  return pins;
}

void StepperBits::turboOn()
{
  if(!(stepNumber%2)) stepNumber++;
}

void StepperBits::turboOff()
{
  stepNumber= (stepNumber/2)*2;
}

void StepperBits::halfStepOn()
{
  stepInc= 1;
}

void StepperBits::halfStepOff()
{
  stepInc= 2;
}

boolean StepperBits::halfStep()
{
  return stepInc==1;
}

// --------------------------------------------------------------------------
// StepperControl
//

StepperControl::StepperControl():StepperBits()
{

}

StepperControl::StepperControl(byte motorID, StpSingleOwner* owner):StepperBits()
{
  this->motorID= motorID;
  this->owner= owner;
}

void StepperControl::begin(uint startSpeed, uint cruiseSpeed)
{
  brakeCutPercent= STP_BRAKE_CUT_PERCENT;
  pulsesToCruise= (cruiseSpeed-startSpeed)/2;
  this->startSpeed= startSpeed;
  this->cruiseSpeed= cruiseSpeed;
}

void StepperControl::beginPins(int mPin1, int mPin2, int mPin3, int mPin4)
{
  StepperBits::begin(mPin1, mPin2, mPin3, mPin4);
}

long StepperControl::getReportCount()
{
  return reportCount;
}

void StepperControl::clearReportCount()
{
  reportCount=0;
}

void StepperControl::setBrakeCutPercent(byte brakeCutPercent)
{
  this->brakeCutPercent= min(100, brakeCutPercent);
}

void StepperControl::enableAutoRun()
{
  autoRunOn= true;
}
  
void StepperControl::moveOn(TStepDirection direction, float ratio, boolean oddOnly)
{
  moveSteps(direction, 0x0FFFFFFF, ratio, oddOnly);
}

void StepperControl::setSpeedParams(float ratio)
{
  startTime= ratio*1000000.0/startSpeed;
  stepTime = startTime;
  
  float cruiseTime= ratio*1000000.0/cruiseSpeed;
  timeInc= (cruiseTime-startTime)/pulsesToCruise;
}

void StepperControl::moveSteps(TStepDirection direction, long steps, float ratio, boolean oddOnly)
{
  nextStep= micros()+20;
  setSpeedParams(ratio);

  stepsToGo= round(steps);
  stepTime = startTime;
  stepsCount= 0;
  reportCount= 0;

  moveDir= direction;
  oddStep= true;
  this->oddOnly= oddOnly;

  brakeOn= direction==stpDir_Stay;
  cutNow= false;
}

void StepperControl::autoRun()
{
  if(!stepsToGo) return;

  ulong mcs= micros();
    
  if(cutNow && mcs>=nextCut){
    motorOff();
    cutNow= false;
  }
    
  if(mcs< nextStep) return;

  if(oddOnly)
  {
    if(oddStep)
      doNextStep(moveDir);
    else
    {
      doNextStep(stpDir_Stay);
      cutNow= true;
    }
    oddStep= !oddStep;
  }
  else
    doNextStep(moveDir);

  stepsCount++;
  stepsToGo--;
  reportCount++;

  if(stepsToGo)
  {
    int accelStat= 0;
    if(stepsToGo<pulsesToCruise) accelStat= -1;
    else 
      if(stepsCount<pulsesToCruise) accelStat= 1;

    if(accelStat)stepTime+= timeInc*accelStat;

    if(brakeOn || cutNow){
      nextCut= nextStep + stepTime*brakeCutPercent/100;
      cutNow= true;
    }
    nextStep+= stepTime;
  }
  else{
    motorOff();
    cutNow= false;
    moveDone= true;
  } 
}

void StepperControl::run()
{
  if(!autoRunOn) autoRun();

  if(moveDone && owner)
  {
    moveDone= false;
    owner->onMoveDone(motorID, stepsCount);
  }
}

void StepperControl::stopNow(){
  if(stepsToGo) stepsToGo= 1;
}

void StepperControl::decelStop(){
  stepsToGo= min(stepsToGo, pulsesToCruise);
}

boolean StepperControl::isMoving(){
  return stepsToGo>0;
}
  

