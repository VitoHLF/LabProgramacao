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

#include "pStpCouple.h"

typedef struct 
{
  TStepDirection left, right;
} 
TStpMovePins;

extern TStpMovePins mvTable[mv_Moves];



TStpMovePins mvTable[mv_Moves] =
{   // left          right 
  { stpDir_Stay , stpDir_Stay  },  //  0: move off
  { stpDir_Ahead, stpDir_Ahead },  //  1: move ahead
  { stpDir_Back , stpDir_Back  },  //  2: move back
  { stpDir_Stay , stpDir_Stay  },  //  3: brake (freio com as bobinas ativadas)
  { stpDir_Back , stpDir_Ahead },  //  4: spin left
  { stpDir_Ahead, stpDir_Back  },  //  5: spin right
  { stpDir_Stay , stpDir_Ahead },  //  6: turn left
  { stpDir_Ahead, stpDir_Stay  },  //  7: turn right
  { stpDir_Stay , stpDir_Back  },  //  8: back turn left
  { stpDir_Back , stpDir_Stay  },  //  9: back turn right
  { stpDir_Ahead, stpDir_Ahead },  // 10: curve left
  { stpDir_Ahead, stpDir_Ahead }   // 11: curve right
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// StpDuoParam
//

#ifdef STP_USE_TIMER2
StpDuoParam::StpDuoParam():StpDuoTimer2() { }
#else
StpDuoParam::StpDuoParam():StpDuoBuff() { }
#endif

void StpDuoParam::begin(uint startSpeed, uint cruiseSpeed, float wheelsDistance, uint turnStepsLf, uint turnStepsRg)
{
#ifdef STP_USE_TIMER2
  StpDuoTimer2::begin(startSpeed, cruiseSpeed);
#else
  StpDuoBuff::begin(startSpeed, cruiseSpeed);
#endif

  distRef = 2*PI*wheelsDistance;
  if(!turnStepsRg)
    turnStepsRg= turnStepsLf;

  // É invertido mesmo
  lfRef= turnStepsRg;
  rgRef= turnStepsLf;

  sprint2d("\n\nspeeds", startSpeed, cruiseSpeed, "\t ");
  sprint2d("turnSteps", turnStepsLf, turnStepsRg, "\n");
  sprint3("wheelsDist: ", wheelsDistance, "\t ");
  sprint3("turnPerim: ", distRef, "\n");
}

void StpDuoParam::move(TMoveParam* mov)
{
  move(mov->mvType, mov->param);
}

boolean StpDuoParam::addMove(byte mvType, float moveParam)
{
  return addMoveSteps(mvType, calcSteps(mvType, moveParam, lfRef), 
                              calcSteps(mvType, moveParam, rgRef));
}

boolean StpDuoParam::addMove(TMoveParam* mov)
{
  return addMove(mov->mvType, mov->param);
}

void StpDuoParam::move(byte mvType, float moveParam)
{
  moveSteps(mvType, calcSteps(mvType, moveParam, lfRef), 
                    calcSteps(mvType, moveParam, rgRef));
}

float StpDuoParam::calcParam(byte mvType, long steps, long ref)
{
  switch(mvType)
  {
    case mv_Brake:
      return steps;

    case mv_TurnLf:
    case mv_TurnBkLf:
    case mv_TurnRg:
    case mv_TurnBkRg:
      return steps*360.0/ref;

    case mv_SpinRg:
    case mv_SpinLf:
      return steps*720.0/ref;

    case mv_CurveLf:
    case mv_CurveRg:
      return steps*180.0/ref;

    case mv_Ahead:
    case mv_Back:
      return steps*distRef/ref;

    default:
      return 0;
  }
}

long StpDuoParam::calcSteps(byte mvType, float moveParam, long ref)
{
  switch(mvType)
  {
    case mv_Brake:
      return round(moveParam);

    case mv_Ahead:
    case mv_Back:
      return round(moveParam*ref/distRef);

    case mv_TurnLf:
    case mv_TurnBkLf:
    case mv_TurnRg:
    case mv_TurnBkRg:
      return round(moveParam*ref/360);

    case mv_SpinRg:
    case mv_SpinLf:
      return round(moveParam*ref/720);

    case mv_CurveLf:
    case mv_CurveRg:
      return round(moveParam*ref/180);

    default:
      return 0;
  }
}

void StpDuoParam::onMoveStepsDone(byte mvType, long stepsLf, long stepsRg)
{
  float param= (calcParam(mvType, stepsLf, lfRef)+ 
                calcParam(mvType, stepsRg, rgRef))/2;

  switch(mvType)
  {
    case mv_Brake:
    case mv_Off:
      onMoveDone(mvType, 0, 0);
      break;

    case mv_Ahead:
    case mv_Back:
      onMoveDone(mvType, 0, param);
      break;

    case mv_SpinLf:
    case mv_SpinRg:
      onMoveDone(mvType, param, 0);
      break;

    case mv_TurnLf:
    case mv_TurnRg:
    case mv_TurnBkLf:
    case mv_TurnBkRg:
      onMoveDone(mvType, param, param*distRef/720);
      break;

    case mv_CurveLf:
    case mv_CurveRg:
      onMoveDone(mvType, param, param*distRef/240);
      break;
  }
}

void StpDuoParam::onStartMoveSteps(byte mvType, long stepsLf, long stepsRg)
{
  float param= (calcParam(mvType, stepsLf, lfRef)+ 
                calcParam(mvType, stepsRg, rgRef))/2;
  onStartMove(mvType, param);
}

void StpDuoParam::onStepsReport(long stepsLf, long stepsRg)
{
  byte mvType= getMoveType();
  if(mvType==mv_Brake) return;
  if(mvType==mv_Off) return;

  float param= (calcParam(mvType, stepsLf, lfRef)+ 
                calcParam(mvType, stepsRg, rgRef))/2;

  switch(mvType)
  {
    case mv_Ahead:
    case mv_Back:
      onMoveReport(0, param);
      break;

    case mv_SpinLf:
    case mv_SpinRg:
      onMoveReport(param, 0);
      break;

    case mv_TurnLf:
    case mv_TurnRg:
    case mv_TurnBkLf:
    case mv_TurnBkRg:
      onMoveReport(param, param*distRef/720);
      break;

    case mv_CurveLf:
    case mv_CurveRg:
      onMoveReport(param, param*distRef/240);
      break;
  }
}

#ifdef STP_USE_TIMER2
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// StpDuoTimer2
//

StpDuoTimer2::StpDuoTimer2():StpDuoBuff(), Timer2()
{
}

void StpDuoTimer2::begin(uint startSpeed, uint cruiseSpeed)
{
  StpDuoBuff::begin(startSpeed, cruiseSpeed);
  enableAutoRun();  
  Timer2::startMicros(STP_TIMER2_TIME);
}

void StpDuoTimer2::onTimerEvent()
{
  StpDuoBuff::autoRun();
}

ulong StpDuoTimer2::overlaps()
{ 
  return Timer2::overlaps(); 
}
#endif

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// StpDuoBuff
//

StpDuoBuff::StpDuoBuff():StepperDuo(), CircularBuffer() {}

void StpDuoBuff::begin(uint startSpeed, uint cruiseSpeed)
{
  StepperDuo::begin(startSpeed, cruiseSpeed);
  CircularBuffer::begin(STP_MAX_BUFF_MOVES, sizeof(TMoveParam));
}

boolean StpDuoBuff::addMoveSteps(byte mvType, long stepsLf, long stepsRg)
{
  TMoveParam mov;
  return addItem(makeMoveParam(&mov, mvType, stepsLf, stepsRg));
}

boolean StpDuoBuff::addMoveSteps(TMoveParam* mov)
{
  return addItem(mov);
}

TMoveParam* StpDuoBuff::getNextMove(TMoveParam* mov)
{
  return (TMoveParam*)getFirst(mov);
}

void StpDuoBuff::clearMoves()
{
  clear();
  executeOn= false;
}

byte StpDuoBuff::movesCount()
{
  return itemsCount();
}

TMoveParam* StpDuoBuff::checkLastMove()
{
  return (TMoveParam*)checkLast();
}

void StpDuoBuff::goNow()
{
  executeOn= true;
  if(itemsCount())
  {
    TMoveParam mov;
    moveSteps(getNextMove(&mov));
  }
  else
    executeOn= false;
}

void StpDuoBuff::moveStepsDoneEvent(byte mvType, long stepsLf, long stepsRg)
{
  onMoveStepsDone(mvType, stepsLf, stepsRg);

  if(!executeOn) return;

  if(itemsCount())
  {
    TMoveParam mov;
    moveSteps(getNextMove(&mov));
  }
  else{
    executeOn= false;
    onAllMovesDone();
  }
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
// StepperDuo
//

StepperDuo::StepperDuo(): StpSingleOwner()
{ 
  mtLf= new StepperSingle(lfMotorID, this);
  mtRg= new StepperSingle(rgMotorID, this);
}

void StepperDuo::begin(uint startSpeed, uint cruiseSpeed)
{
  mtLf->begin(startSpeed, cruiseSpeed);
  mtRg->begin(startSpeed, cruiseSpeed);
}

void StepperDuo::beginLf(int mPin_1, int mPin_2, int mPin_3, int mPin_4)
{
  mtLf->beginPins(mPin_1, mPin_2, mPin_3, mPin_4);
}

void StepperDuo::beginRg(int mPin_1, int mPin_2, int mPin_3, int mPin_4)
{
  mtRg->beginPins(mPin_1, mPin_2, mPin_3, mPin_4);
}

void StepperDuo::enableAutoRun()
{
  mtLf->enableAutoRun();
  mtRg->enableAutoRun();
}

void StepperDuo::setReportSteps(long steps)
{
  reportSteps= steps;
}

void StepperDuo::moveSteps(byte mvType, long stepsLf, long stepsRg)
{
  moveType= mvType;
  float ratioLf= 1, ratioRg= 1;

  if(!stepsRg) stepsRg= stepsLf;
  else{
    long maxSteps= max(stepsLf, stepsRg);
    ratioRg= (float)stepsLf/maxSteps;
    ratioLf= (float)stepsRg/maxSteps;
  }

  onStartMoveSteps(mvType, stepsLf, stepsRg);

  sprint2d("steps", stepsLf, stepsRg, "\t ");
  sprint2d("ratio", ratioLf, ratioRg, "\n");

  mtLf->moveSteps(mvTable[mvType].left, stepsLf, ratioLf, mvType==mv_CurveLf);
  mtRg->moveSteps(mvTable[mvType].right, stepsRg, ratioRg, mvType==mv_CurveRg);
}

void StepperDuo::moveSteps(TMoveParam* mov)
{
  moveSteps(mov->mvType, mov->stepsLf, mov->stepsRg);
}

TMoveParam* StepperDuo::makeMoveParam(TMoveParam* mov, byte mvType, long stepsLf, long stepsRg)
{
  mov->mvType= mvType;
  mov->stepsLf= stepsLf;
  mov->stepsRg= stepsRg?stepsRg:stepsLf;
  return mov;
}

void StepperDuo::moveOn(byte mvType)
{
  moveType= mvType;
  mtLf->moveOn(mvTable[mvType].left, mvType==mv_CurveLf);
  mtRg->moveOn(mvTable[mvType].right, mvType==mv_CurveRg);
}

void StepperDuo::autoRun()
{
  mtLf->autoRun();
  mtRg->autoRun();
}

void StepperDuo::run()
{
  mtLf->run();
  mtRg->run();
  if(reportSteps)
  {
    if(min(mtLf->getReportCount(), mtRg->getReportCount()) >= reportSteps )
    {
      onStepsReport(mtLf->getReportCount(), mtRg->getReportCount());
      mtLf->clearReportCount(); 
      mtRg->clearReportCount();
    }
  }
}

void StepperDuo::halfStepOn()
{
  mtLf->halfStepOn();
  mtRg->halfStepOn();
}

void StepperDuo::halfStepOff()
{
  mtLf->halfStepOff();
  mtRg->halfStepOff();
}

boolean StepperDuo::halfStep()
{
  return mtLf->halfStep() || mtRg->halfStep();
}

void StepperDuo::turboOn()
{
  mtLf->turboOn();
  mtRg->turboOn();
}

void StepperDuo::turboOff()
{
  mtLf->turboOff();
  mtRg->turboOff();
}

void StepperDuo::motorOff()
{ 
  mtLf->motorOff();
  mtRg->motorOff();
} 

void StepperDuo::stopNow()
{
  mtLf->stopNow();
  mtRg->stopNow();
}
  
void StepperDuo::decelStop()
{
  mtLf->decelStop();
  mtRg->decelStop();
}
  
boolean StepperDuo::isMoving()
{
  return mtLf->isMoving() || mtRg->isMoving();
}

void StepperDuo::onMoveDone(byte motorID, long steps)
{
  static long stpLf=0;
  static long stpRg=0;

  if(motorID== lfMotorID) stpLf= steps;
  if(motorID== rgMotorID) stpRg= steps;
  if(stpLf && stpRg)
  {
    moveStepsDoneEvent(moveType, stpLf, stpRg);
    stpLf=0;
    stpRg=0;
  }
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// StepperCouple
//

StepperCouple::StepperCouple():StpDuoParam()
{

}

void StepperCouple::begin(uint startSpeed, uint cruiseSpeed, float wheelsDistance, uint turnStepsLf, uint turnStepsRg)
{
  StpDuoParam::begin(startSpeed, cruiseSpeed, wheelsDistance, turnStepsLf, turnStepsRg);
}

void StepperCouple::beginLf(int mPin_1, int mPin_2, int mPin_3, int mPin_4)
{ 
  StpDuoParam::beginLf(mPin_1, mPin_2, mPin_3, mPin_4);   
}

void StepperCouple::beginRg(int mPin_1, int mPin_2, int mPin_3, int mPin_4)
{ 
  StpDuoParam::beginRg(mPin_1, mPin_2, mPin_3, mPin_4);   
}

void StepperCouple::move(TMoveParam* mov)
{
  StpDuoParam::move(mov);
}

void StepperCouple::move(byte movType, float moveParam)
{
  StpDuoParam::move(movType, moveParam);
}

boolean StepperCouple::addMove(byte mvType, float moveParam)
{
  return StpDuoParam::addMove(mvType, moveParam);
}

boolean StepperCouple::addMove(TMoveParam* mov)
{
  return StpDuoParam::addMove(mov);
}

void StepperCouple::setReportSteps(long steps)    
{ 
  StpDuoParam::setReportSteps(steps);   
}

void StepperCouple::turboOn()    
{ 
  StpDuoParam::turboOn();   
}

void StepperCouple::turboOff()    
{ 
  StpDuoParam::turboOff();   
}

void StepperCouple::halfStepOn()    
{ 
  StpDuoParam::halfStepOn();   
}

void StepperCouple::halfStepOff()    
{ 
  StpDuoParam::halfStepOff();   
}

void StepperCouple::run()
{
  StpDuoParam::run();   
}

void StepperCouple::moveSteps(byte mvType, long stepsLf, long stepsRg)
{
  StpDuoParam::moveSteps(mvType, stepsLf, stepsRg);   
}

void StepperCouple::moveOn(byte mvType)
{
  StpDuoParam::moveOn(mvType);   
}

void StepperCouple::stopNow()
{
  StpDuoParam::stopNow();   
}

void StepperCouple::decelStop()
{
  StpDuoParam::decelStop();   
}

void StepperCouple::motorOff()
{
  StpDuoParam::motorOff();   
}

boolean StepperCouple::isMoving()
{
  return StpDuoParam::isMoving();   
}

byte StepperCouple::getMoveType() 
{ 
  return StpDuoParam::getMoveType();   
}

void StepperCouple::goNow()
{
  StpDuoParam::goNow();   
}

void StepperCouple::clearMoves()
{
  StpDuoParam::clearMoves();   
}

byte StepperCouple::movesCount()
{
  return StpDuoParam::movesCount();   
}

#ifdef STP_USE_TIMER2
ulong StepperCouple::overlaps()
{
  return StpDuoParam::overlaps();
}
#endif
