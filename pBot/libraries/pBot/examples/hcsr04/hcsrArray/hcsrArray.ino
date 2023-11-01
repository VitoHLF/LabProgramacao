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

// HcsrArray class example.

#include <pHcsr04.h>

#define HC_LEFT_TRIG_PIN    2
#define HC_LEFT_ECHO_PIN    3
#define HC_FRONT_TRIG_PIN   4 
#define HC_FRONT_ECHO_PIN   5
#define HC_RIGHT_TRIG_PIN   6
#define HC_RIGHT_ECHO_PIN   7
#define MAX_HC_SENSORS      3

#define READ_LAPSE      150  // milliseconds
#define WARNING_DIST     15  // centimeters

class MyHcsrArray: public HcsrArray
{
public:
  int hcLeftID, hcFrontID, hcRightID;
  
  void begin()
  {
    if(!HcsrArray::begin(MAX_HC_SENSORS, centimeter))
    {
      sprint("Insufficient memory to alloc array");
      while(1)
        ;
    }
    hcLeftID = addHcSensor(HC_LEFT_TRIG_PIN , HC_LEFT_ECHO_PIN);
    // hcLeftID == 0
    hcFrontID= addHcSensor(HC_FRONT_TRIG_PIN, HC_FRONT_ECHO_PIN);
    // hcFrontID == 1
    hcRightID= addHcSensor(HC_RIGHT_TRIG_PIN, HC_RIGHT_ECHO_PIN);
    // hcRightID == 2

    if(hcLeftID<0 || hcFrontID<0 || hcRightID<0)
    {
      sprint("Error adding sensor.");
      while(1)
        ;
    }

    patrolModeOn(READ_LAPSE);
  }

  void onPatrolDone()
  {
    sprint2("Left: ", getLastDist(hcLeftID));
    sprint2("\t Front: ", getLastDist(hcFrontID));
    sprint2("\t Right: ", getLastDist(hcRightID));
    sprint2("\t Max: ", getMaxDist());
    sprint3("\t Min: ", getMinDist(), "\n");
  }

  void onNextHcRead(byte hcID, int dist)
  {
    if(dist < WARNING_DIST)
    {
      if(hcID==hcLeftID) sprint(">>> Left warning: ");
      else
        if(hcID==hcFrontID) sprint(">>> Front warning: ");
        else
          if(hcID==hcRightID) sprint(">>> Right warning: ");
      
      sprint2(dist, "cm\n");
    }
  }
};

MyHcsrArray hca;

void setup() 
{
  Serial.begin(57600);
  hca.begin();
}

void loop() 
{
  hca.run();
}
