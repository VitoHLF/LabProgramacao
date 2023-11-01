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

// Example of PushButtonArray class usage

#include <pPushButton.h>

#define BUTTON_1_PIN   2
#define BUTTON_2_PIN   3
#define BUTTON_3_PIN   4
#define BUTTON_4_PIN   5

class MyButtonArrayClass: public PushButtonArray
{
public:
  byte bt1ID, bt2ID, bt3ID, bt4ID; // Buttons IDs
  
  void begin()
  {
    if(!PushButtonArray::begin(4))
      Serial.println(F("Error!!! Insuficient memory."));
      
    bt1ID= addButton(BUTTON_1_PIN, true);
    bt2ID= addButton(BUTTON_2_PIN, true);
    bt3ID= addButton(BUTTON_3_PIN, true);
    bt4ID= addButton(BUTTON_4_PIN, true);
  }

  void onButtonPressed(byte btID)
  {
    if(btID == bt1ID) Serial.println(F("Button 1 pressed."));
    if(btID == bt2ID) Serial.println(F("Button 2 pressed."));
    if(btID == bt3ID) Serial.println(F("Button 3 pressed."));
    if(btID == bt4ID) Serial.println(F("Button 4 pressed."));
  }
  
  void onButtonReleased(byte btID)
  {
    if(btID == bt1ID) Serial.println(F("Button 1 released."));
    if(btID == bt2ID) Serial.println(F("Button 2 released."));
    if(btID == bt3ID) Serial.println(F("Button 3 released."));
    if(btID == bt4ID) Serial.println(F("Button 4 released."));
  }
};

MyButtonArrayClass bta;

void setup() 
{
  Serial.begin(57600);
  bta.begin();
}

void loop() 
{
  bta.run();
}
