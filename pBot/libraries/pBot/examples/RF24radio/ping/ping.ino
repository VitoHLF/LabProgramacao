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

// RadioMessage class example

#include <pRadioMsg.h>

#define CE_PIN    9
#define CS_PIN   10

uint8_t pipeIn [7]= "1RNode";
uint8_t pipeOut[7]= "0RNode";

#define LAPSE_TIME 200

typedef struct
{
  float time;
  long serial;
} 
TPack;

void updatePack(TPack* pack)
{
  pack->time= millis()/1000.0;
  pack->serial++;
}

void printPack(TPack* pack)
{
  sprint2(" Time: ", pack->time);
  sprint3(" [", pack->serial, "]\n");
}


RadioMessage rm(CE_PIN, CS_PIN);
TPack pack;

unsigned long nextTx= 0;
boolean myTurn= true;

void setup() 
{
 Serial.begin(57600);
 rm.begin(pipeIn, pipeOut, RF24_250KBPS);
 pack.serial= 0;
 
 Serial.println("\nInit loop\n");
}

TRadioMsg msg;

void loop() 
{
  if(myTurn && nextTx<millis())
  {
    updatePack(&pack);
    rm.makeMessage(&msg, 0, sizeof(pack), &pack);
    rm.sendMessage(&msg);
    sprint(">>>>>> "); printPack(&pack);
    myTurn= false;
  }

  if(rm.messageWaiting())
  {
    rm.readMessage(&msg);
    rm.copyMsgPayload(&msg, &pack);
    sprint("\t\t\t\t<<<<<< "); printPack(&pack);
    myTurn= true;
    nextTx= millis()+LAPSE_TIME;
  }
}
