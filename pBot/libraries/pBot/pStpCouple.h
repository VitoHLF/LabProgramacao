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

#ifndef pStpCouple_h
#define pStpCouple_h

#include <pStpMotor.h>
#include <pTimer2.h>
#include <pCircBuff.h>

// Se preferir não usar o timer2 para a temporização dos pulsos,
// comente este define
//
#define STP_USE_TIMER2

// Intervalo para o Timer2 em microssegundos
//
#define STP_TIMER2_TIME 64 

#define rgMotorID 1
#define lfMotorID 2

typedef struct
{
  byte mvType;
  union{
    struct{
      long  stepsLf; 
      long  stepsRg; 
    };
    float param;
  };
}
TMoveParam;

// ---------------------------------------------------------------------------
// StepperDuo - Controla e sincroniza dois motores de passo para executar 
//              os movimentos implementados.

class StepperDuo: public StpSingleOwner {
public:
	StepperDuo();
  void begin(uint startSpeed, uint cruiseSpeed);
	void beginLf(int mPin_1, int mPin_2, int mPin_3, int mPin_4);
	void beginRg(int mPin_1, int mPin_2, int mPin_3, int mPin_4);
  void setReportSteps(long steps);
  void turboOn();
  void turboOff();
  void halfStepOn();
  void halfStepOff();
  void run();

  TMoveParam* makeMoveParam(TMoveParam* mov, byte mvType, long stepsLf, long stepsRg=0);
  void moveSteps(TMoveParam* mov);
  void moveSteps(byte mvType, long stepsLf, long stepsRg=0);
  void moveOn(byte mvType);
  void stopNow();
  void decelStop();
  void motorOff();

  boolean isMoving();
  byte getMoveType() { return moveType;  }
  boolean halfStep();

protected:
  void enableAutoRun();
  void autoRun();

  virtual void moveStepsDoneEvent(byte mvType, long stepsLf, long stepsRg){}
  virtual void onStartMoveSteps(byte mvType, long stepsLf, long stepsRg){}
  virtual void onStepsReport(long stepsLf, long stepsRg){}

private:
  StepperSingle *mtLf, *mtRg;
  byte moveType;
  long reportSteps=0;
  
  void onMoveDone(byte motorID, long steps);
};


#define STP_MAX_BUFF_MOVES  16

// ---------------------------------------------------------------------------
// StpDuoBuff - Acrescenta um buffer circular de movimentos. Permite armazenar 
//              uma sequencia de movimentos e executá-los automaticamente.
//
class StpDuoBuff: public StepperDuo, private CircularBuffer {
public:
  StpDuoBuff();

  void begin(uint startSpeed, uint cruiseSpeed);

  boolean addMoveSteps(byte mvType, long stepsLf, long stepsRg=0);
  boolean addMoveSteps(TMoveParam* mov);
  void goNow();
  void clearMoves();
  byte movesCount();

protected:
  virtual void onAllMovesDone(){}
  virtual void onMoveStepsDone(byte mvType, long stepsLf, long stepsRg){}

private:
  boolean executeOn= false;

  TMoveParam* getNextMove(TMoveParam* mov);
  TMoveParam* checkLastMove();
  void moveStepsDoneEvent(byte mvType, long stepsLf, long stepsRg);
};

#ifdef STP_USE_TIMER2
// ---------------------------------------------------------------------------
// StpDuoTimer2 - Usa o timer2 do arduino para a temporização dos passos. 
//
class StpDuoTimer2: public StpDuoBuff, private Timer2 {
public:
  StpDuoTimer2();
  void begin(uint startSpeed, uint cruiseSpeed);
  ulong overlaps();

private:
  void onTimerEvent();
};
#endif

// ----------------------------------------------------------------------------------
// StpDuoParam - A partir daqui os movimentos passam a ser informados em cm e graus
//

#ifdef STP_USE_TIMER2
class StpDuoParam: public StpDuoTimer2 {
#else
class StpDuoParam: public StpDuoBuff {
#endif  
public:
  StpDuoParam();

  void begin(uint startSpeed, uint cruiseSpeed, float wheelsDistance, uint turnStepsLf, uint turnStepsRg=0);
  void move(byte movType, float moveParam);
  void move(TMoveParam* mov);
  boolean addMove(byte mvType, float moveParam);
  boolean addMove(TMoveParam* mov);

protected:
  virtual void onStartMove(byte mvType, float moveParam){}
  virtual void onMoveDone(byte mvType, float arc, float dist){}
  virtual void onMoveReport(float arc, float dist){}

private:
  long lfRef, rgRef;
  float distRef;
  float moveParam;

  long calcSteps(byte mvType, float moveParam, long ref);
  float calcParam(byte mvType, long steps, long ref);

  void onMoveStepsDone(byte mvType, long stepsLf, long stepsRg);
  void onStepsReport(long stepsLf, long stepsRg);
  void onStartMoveSteps(byte mvType, long stepsLf, long stepsRg);
};

// ----------------------------------------------------------------------------------
// StepperCouple - Classe para publicação
//
class StepperCouple: private StpDuoParam {
public:
  // Construction
  StepperCouple();

  // Initialization
  void begin(uint startSpeed, uint cruiseSpeed, float wheelsDistance, uint turnStepsLf, uint turnStepsRg=0);
  void beginLf(int mPin_1, int mPin_2, int mPin_3, int mPin_4);
  void beginRg(int mPin_1, int mPin_2, int mPin_3, int mPin_4);
  void turboOn();
  void turboOff();
  void halfStepOn();
  void halfStepOff();
  void setReportSteps(long steps);

  //Calibration
  void moveSteps(byte mvType, long stepsLf, long stepsRg=0);
  void setBrakeCutPercent(byte brakeCutPercent);

  // Operation
  void run();
  void moveOn(byte mvType);
  void move(TMoveParam* mov);
  void move(byte movType, float moveParam);
  boolean addMove(TMoveParam* mov);
  boolean addMove(byte mvType, float moveParam);
  void goNow();
  void clearMoves();
  void stopNow();
  void decelStop();
  void motorOff();

  // Monitoring
  boolean halfStep();
  boolean isMoving();
  byte getMoveType();
  byte movesCount();
#ifdef STP_USE_TIMER2
  ulong overlaps();
#endif
protected:
  virtual void onAllMovesDone(){}
  virtual void onStartMove(byte mvType, float moveParam){}
  virtual void onMoveDone(byte mvType, float arc, float dist){}
  virtual void onMoveReport(float arc, float dist){}
};



#endif
