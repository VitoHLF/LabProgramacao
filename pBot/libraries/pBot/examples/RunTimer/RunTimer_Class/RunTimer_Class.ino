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

#include <pRunTimer.h>

/**
 * Exemplo de uso da classe RunTimer
 * 
 * Neste exemplo é criada uma Classe descendente de RunTimer.
 * O método abstrato onTimerEvent() é reescrito para receber 
 * os eventos do timer. O método run() (herdado de RunTimer)
 * precisa ser chamado frequentemente.
 * 
 */

#define LED_PIN 13

class RunTimerChild: public RunTimer 
{
public:
  void begin()
  {
    pinMode(LED_PIN, OUTPUT);
    startMillis(400);  // Tempo em milissegundos. Para informar o tempo em 
                       // microssegundos use o método startMicros()
  }
  
  void onTimerEvent()
  {
    static boolean ledStatus= false;
    
    ledStatus= !ledStatus;
    digitalWrite(LED_PIN, ledStatus);
  }
};

 
RunTimerChild rtc;

void setup()
{
  rtc.begin();
}

void loop()
{
  rtc.run();
}

