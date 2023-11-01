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

// Example of JoyStick class usage

#include <pJoystick.h>

#define XAXIS_PIN   A0
#define YAXIS_PIN   A1
#define ZBUTTON_PIN 8

#define NORMALIZE_XY_TO  100    // XY values range's  -100 to 100
#define TOLERANCE          3    // Minimum axis variation to trigger event (after normalize)
#define Z_IGNORE_XY     true    // Ignore XY events when button Z is pressed

class JoyStickClass: public JoyStick
{
public:
  void begin()
  {
    JoyStick::begin(XAXIS_PIN, YAXIS_PIN, ZBUTTON_PIN);
    axisConfig(NORMALIZE_XY_TO, TOLERANCE, Z_IGNORE_XY);
  }

  void onZButtonPressed()
  {
    Serial.println("Z button pressed.");
  }

  void onZButtonReleased()
  {
    Serial.println("Z button released.");
  }

  void onXAxisChange(int xVal)
  {
    Serial.print("X: ");
    Serial.println(xVal);
  }
  
  void onYAxisChange(int yVal)
  {
    Serial.print("\t\t Y: ");
    Serial.println(yVal);
  }
};

JoyStickClass jsc;

void setup() 
{
  Serial.begin(57600);
  jsc.begin();
}

void loop() 
{
  jsc.run();
}

