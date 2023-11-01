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
#define WARNING_DIST     10  // centimeters

HcsrArray hca;
int hcLeftID, hcFrontID, hcRightID;
  
void doNewHcRead()
{
    int lastDist= hca.getLastDist();
    if(lastDist < WARNING_DIST)
    {
      byte hcID= hca.lastHcID();
      if(hcID==hcLeftID) sprint(">>> Left warning: ");
      else
        if(hcID==hcFrontID) sprint(">>> Front warning: ");
        else
          if(hcID==hcRightID) sprint(">>> Right warning: ");
      
      sprint2(lastDist, "cm\n");
    }
}

void doPatrolDone()
{
  sprint2("Left: ", hca.getLastDist(hcLeftID));
  sprint2("\t Front: ", hca.getLastDist(hcFrontID));
  sprint2("\t Right: ", hca.getLastDist(hcRightID));
  sprint2("\t Max: ", hca.getMaxDist());
  sprint2("\t Min: ", hca.getMinDist());
  sprint("\n");
}

void setup() 
{
  Serial.begin(57600);
  if(!hca.begin(MAX_HC_SENSORS, centimeter))
  {
    sprint("Insufficient memory to alloc array");
    while(1)
      ;
  }
  
  hcLeftID = hca.addHcSensor(HC_LEFT_TRIG_PIN , HC_LEFT_ECHO_PIN);
  hcFrontID= hca.addHcSensor(HC_FRONT_TRIG_PIN, HC_FRONT_ECHO_PIN);
  hcRightID= hca.addHcSensor(HC_RIGHT_TRIG_PIN, HC_RIGHT_ECHO_PIN);
  
  if(hcLeftID<0 || hcFrontID<0 || hcRightID<0)
  {
    sprint("Error adding sensor.");
    while(1)
      ;
  }

  hca.patroModelOn(READ_LAPSE);
}

void loop() 
{
  if(hca.run())
  {
    doNewHcRead();
    if(hca.isPatrolDone()) 
      doPatrolDone();
  }    
}

