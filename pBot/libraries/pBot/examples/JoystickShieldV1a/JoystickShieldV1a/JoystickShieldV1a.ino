// ---------------------------------------------------------------------------
// pBot Library - v1.1 - 12/03/2019
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

// Example of JoyStickShield class usage

#include <pJs_ShieldV1a.h>

#define NORMALIZE_XY_TO  100    // XY values range's  -100 to 100
#define TOLERANCE          3    // Minimum axis variation to trigger event (after normalize)
#define Z_IGNORE_XY     true    // Ignore XY events when button Z is pressed

class MyJoystickClass: public JoyStickShield
{
  public:
  MyJoystickClass():JoyStickShield(){};
  
  void begin()
  {
    JoyStickShield::begin();
    axisConfig(NORMALIZE_XY_TO, TOLERANCE, Z_IGNORE_XY);
  }

  // Events
  //
  void onButtonPressed(byte buttonID)
  {
    switch(buttonID)
    {
      case BT_A_ID: Serial.println(F("Button A pressed.")); break;
      case BT_B_ID: Serial.println(F("Button B pressed.")); break;
      case BT_C_ID: Serial.println(F("Button C pressed.")); break;
      case BT_D_ID: Serial.println(F("Button D pressed.")); break;
      case BT_E_ID: Serial.println(F("Button E pressed.")); break;
      case BT_F_ID: Serial.println(F("Button F pressed.")); break;
      case BT_Z_ID: Serial.println(F("Button Z pressed.")); break;
    }
  }
  
  void onButtonReleased(byte buttonID)
  {
    switch(buttonID)
    {
      case BT_A_ID: Serial.println(F("Button A released.")); break;
      case BT_B_ID: Serial.println(F("Button B released.")); break;
      case BT_C_ID: Serial.println(F("Button C released.")); break;
      case BT_D_ID: Serial.println(F("Button D released.")); break;
      case BT_E_ID: Serial.println(F("Button E released.")); break;
      case BT_F_ID: Serial.println(F("Button F released.")); break;
      case BT_Z_ID: Serial.println(F("Button Z released.")); break;
    }
  }

  void onXAxisChange(int xVal)
  {
    Serial.print(F("Joystick X axis change: "));
    Serial.println(xVal);
  }
  
  void onYAxisChange(int yVal)
  {
    Serial.print(F("Joystick Y axis change: "));
    Serial.println(yVal);
  }
};

MyJoystickClass js;

void setup() 
{
  Serial.begin(57600);
  js.begin();
}

void loop() 
{
  js.run();
}
