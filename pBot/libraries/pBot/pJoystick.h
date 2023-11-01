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

#ifndef joyStick_h
#define joyStick_h

#include <Arduino.h>
#include "pPushButton.h"

/*
  JoyStick module driver.
  Francesco Artur Perrotti - Fatec Americana

  How to use:
  Derive JoyStick class and rewrite the events:

  virtual void onZButtonPressed()
  virtual void onZButtonReleased()
  virtual void onXAxisChange(int xVal)
  virtual void onYAxisChange(int yVal)

  Call begin() method before any other.

  Call run() method at least once per loop.

  You can configure scale and tolerance to joy stick XY axis calling axisConfig().

  Call pressed() method to verify if Z button is pressed.
*/

class JoyStick: public PushButton
{
public:  
  /* Constructor
  */
  JoyStick():PushButton(){};

  /* Call before any method
  */
  void begin(byte xAxisPin, byte yAxisPin, byte zButtonPin);

  /** Configure joy stick axis
   *  normalizeTo: Value to normalize XY axis reads. 
   *  tolerance: Minimum axis variation to trigger event (after normalize)
   *  zIgnoreXY: Ignore XY axis events when button Z is pressed.
   */
  void axisConfig(int normalizeTo, byte tolerance, boolean zIgnoreXY=true);


  /** Call once per loop
   */
  void run();

  // Read X axis
  //
  int readXAxis();

  // Read Y axys
  //
  int readYAxis();

  // Read Z button
  // Return true if pressed or false if not.
  boolean readZButton();

protected:
  // Events. Rewrite to capture.
  virtual void onZButtonPressed(){}
  virtual void onZButtonReleased(){}
  virtual void onXAxisChange(int xVal){}
  virtual void onYAxisChange(int yVal){}

private:
  int xAxisRef, yAxisRef;
  byte xAxisPin, yAxisPin, zButtonPin;

  int lastX=0, 
      lastY=0;
  long scaleX= 10000, 
       scaleY= 10000;
  byte  tolerance= 1;
  boolean zIgnoreXY= true;

  void onButtonPressed();
  void onButtonReleased();
};

#endif