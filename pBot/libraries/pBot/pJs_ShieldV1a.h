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

#ifndef pJs_ShieldV1a_h
#define pJs_ShieldV1a_h

#include <arduino.h>
#include "pPushButton.h"
#include "pJoystick.h"

/*
  JoyStick Shield V1.A board driver.
  Francesco Artur Perrotti - Fatec Americana

  How to use:
  Derive JoyStickShield class and rewrite the events:

  virtual void onButtonPressed(int buttonID)
  virtual void onButtonReleased(int buttonID)
  virtual void onXAxisChange(int xVal)
  virtual void onYAxisChange(int yVal)

  Call begin() method before any other.

  Call run() method at least once per loop.

  You can configure scale and tolerance to joy stick XY axis calling axisConfig().

  This level do not include radio support. See pJsRadio.h to use nRF24L01 radio.
*/


/*
// Arduino UNO pins
// 
// Digital
//
//  0: RX
//  1: TX
//  2: Button A
//  3: Button B
//  4: Button C
//  5: Button D
//  6: Button E
//  7: Button F
//  8: Button Z
//  9: Radio CE
// 10: Radio CS
// 11: Radio MOSI
// 12: Radio MISO
// 13: Radio SDK
//
// Analogic
//
// A0: X axis
// A1: Y axis
// A2:
// A3:
// A4:
// A5:
*/

// Button's pins
#define BT_A_PIN 2
#define BT_B_PIN 3
#define BT_C_PIN 4
#define BT_D_PIN 5
#define BT_E_PIN 6
#define BT_F_PIN 7
#define BT_Z_PIN 8

// Button's IDs
#define BT_A_ID 0
#define BT_B_ID 1  
#define BT_C_ID 2
#define BT_D_ID 3
#define BT_E_ID 4
#define BT_F_ID 5
#define BT_Z_ID 6

#define JS_BUTTONS 7

// JoyStick pins
#define X_AXIS_PIN A0
#define Y_AXIS_PIN A1

class JoyStickShield: private JoyStick, private PushButtonArray
{
public:  
  /* Constructor
  */
  JoyStickShield();

  /* Call before any method
  */
  void begin();

  /** Configure joystick axis
   *  normalizeTo: Value to normalize reads. 
   *  tolerance: Minimum axis variation to trigger event (after normalize)
   *  zIgnoreXY: Ignore XY axis events when button Z is pressed.
   */
  void axisConfig(int normalizeTo, byte tolerance, boolean zIgnoreXY=false);


  /** Call once per loop
   */
  void run();

  /** Call to verify if a button is pressed.
   *  btId: ID number of button. 
   */
  boolean isPressed(byte btId)
  { 
    if(btId==BT_Z_ID)
      return JoyStick::readZButton();
    else
      return PushButtonArray::isPressed(btID); 
  }

protected:
  // Events. Rewrite to capture.
  virtual void onButtonPressed(byte btID){} // Buttons
  virtual void onButtonReleased(byte btID){}

  virtual void onXAxisChange(int xVal){}    // Joystick axis
  virtual void onYAxisChange(int yVal){}

private:
  void onZButtonPressed(){ onButtonPressed(BT_Z_ID); }
  void onZButtonReleased(){ onButtonReleased(BT_Z_ID); }

};

#endif