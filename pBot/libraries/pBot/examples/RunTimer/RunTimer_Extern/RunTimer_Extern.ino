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
 * Neste exemplo é criada uma função externa para executar o código
 * associado aos eventos do timer. Essa função deve ser informada
 * no construtor de RunTimer e será chamada a cada evento automaticamente. 
 * 
 */

#define LED_PIN 13

void timerEvent()
{
  static boolean ledStatus= false;
  ledStatus= !ledStatus;
  digitalWrite(LED_PIN, ledStatus);
}

RunTimer rtm(timerEvent);

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  rtm.startMillis(400);  // Tempo em milissegundos. Para informar o tempo em 
                         // microssegundos use o método startMicros()
}

void loop() 
{
  rtm.run();
}
