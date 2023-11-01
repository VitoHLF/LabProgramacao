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

// Example of PushButton class usage

#include <pPushButton.h>

#define BUTTON_PIN   2

class MyButtonOwner: public ButtonOwner
{
public:
  void buttonPressed(byte btID)
  {
    Serial.println(F("Button pressed."));
  }
  
  void buttonReleased(byte btID)
  {
    Serial.println(F("Button released."));
  }
};

MyButtonOwner btOw;
PushButton bt(0, &btOw);

void setup() 
{
  Serial.begin(57600);
  bt.begin(BUTTON_PIN, true);
}

void loop() 
{
  bt.run();
}
