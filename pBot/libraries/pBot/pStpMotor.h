// ---------------------------------------------------------------------------
// pBot Library - v1.05 - 01/11/2016
//
// AUTHOR/LICENSE:
// Created by Francesco A. Perrotti - faperrotti@hotmail.com
// Copyright 2014 License: GNU General Public License v3
// http://www.gnu.org/licenses/
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

#ifndef pStpMotor_h
#define pStpMotor_h

#include <pGlobals.h>
#include <pOwners.h>

// Porcentagem de corte no tempo dos pulsos para os motores
//
#define STP_BRAKE_CUT_PERCENT     65

enum TStepDirection { stpDir_Back= -1,  stpDir_Stay= 0, stpDir_Ahead= 1};

// -------------------------------------------------------
// StepperBits: Low level process. No timing for steps.
//
class StepperBits{
public:
  StepperBits(); 
  void begin(int mPin1, int mPin2, int mPin3, int mPin4);

  byte doNextStep(TStepDirection direction);
  void turboOn();
  void turboOff();
  void halfStepOn();
  void halfStepOff();
  boolean halfStep();
  void motorOff();

  // desprotegido, não chamar diretamente
  void motorPinsOut(byte pins);

private:
  byte stepNumber;
  byte stepInc;
  int mPin_1, mPin_2, mPin_3, mPin_4;
};

// -------------------------------------------------------
// StepperControl: Manage timming and events. Take care of 
//                 move details. Add energy cutoff feature 
//  to protect hardware. Introduce accerelation and 
//  decelerarion capacity.
//
class StepperControl: public StepperBits
{
public:
  StepperControl();
  StepperControl(byte motorID, StpSingleOwner* owner);

  void begin(uint startSpeed, uint cruiseSpeed);
  void beginPins(int mPin1, int mPin2, int mPin3, int mPin4);
  void setBrakeCutPercent(byte brakeCutPercent);
  void enableAutoRun();

  void moveSteps(TStepDirection direction, long steps, float ratio=1, boolean oddOnly= false);
  void moveOn(TStepDirection direction, float ratio=1, boolean oddOnly= false);
  void run();
  void stopNow();
  void decelStop();

  long getReportCount();
  void clearReportCount();
  boolean isMoving();

protected:
  // Unprotected, do not call directly
  void autoRun();
  
private:
  byte motorID;
  StpSingleOwner* owner= NULL;
  long reportCount= 0;
  long stepsCount=0, stepsToGo=0;
  uint pulsesToCruise;
  byte brakeCutPercent;
  uint startSpeed, cruiseSpeed;

  float startTime;
  float stepTime, timeInc;
  float nextStep, nextCut;

  TStepDirection moveDir;

  boolean autoRunOn= false,
          moveDone= false,
          brakeOn = false, 
          cutNow = false,
          oddOnly= false,
          oddStep= true;

  void setSpeedParams(float ratio);
};


// -------------------------------------------------------
// StepperSingle: Publish class
//                 
class StepperSingle: private StepperControl
{
public:
  // Construction
  StepperSingle();
  StepperSingle(byte motorID, StpSingleOwner* owner);

  // Initialization
  void begin(uint startSpeed, uint cruiseSpeed);
  void beginPins(int mPin1, int mPin2, int mPin3, int mPin4);
  void setBrakeCutPercent(byte brakeCutPercent);
  void enableAutoRun();
  void turboOn();
  void turboOff();
  void halfStepOn();
  void halfStepOff();

  // Operation
  void run();
  void moveSteps(TStepDirection direction, long steps, float ratio=1, boolean oddOnly= false);
  void moveOn(TStepDirection direction, float ratio=1, boolean oddOnly= false);
  void stopNow();
  void decelStop();
  void motorOff();

  // Monitoring
  boolean isMoving();
  boolean halfStep();
  long getReportCount();
  void clearReportCount();

  // Unprotected, do not call directly
  void autoRun();
};

#endif
