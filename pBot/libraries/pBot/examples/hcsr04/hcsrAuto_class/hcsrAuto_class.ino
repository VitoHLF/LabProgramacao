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

// HcsrAuto class example.

#include <pHcsr04.h>

/**
 * Exemplo de uso da classe HcsrAuto usando uma classe descendente para 
 * capturar o evento onHcRead()
 * 
 * Chame o método begin() antes de qualquer outro método para informar os pinos que serão usados e 
 * a unidade de distância (centimetros ou polegadas). 
 * Use o método hcStart() para iniciar as leituras automáticas e informar o tempo entre as leituras.
 * O método hcStop interrompe as leituras automáticas.
 * O método run() deve ser chamado a cada iteração do loop principal. 
 */

#define trigPin 2
#define echoPin 3

class HcsrAutoChild: public HcsrAuto
{
public:
  void begin()
  {
    HcsrAuto::begin(trigPin, echoPin, centimeter);
    hcStart(500); // Tempo entre leituras em milissegundos
  }

  void onHcRead(int dist)
  {
    if(dist<0)
      sprint("Fora de alcance ou erro de leitura.");
    else
      sprint2("Dist: ", dist);  
    sprint("\n");
  }
};

HcsrAutoChild hac;

void setup() 
{
  Serial.begin(57600);
  hac.begin();
}

void loop() 
{
  hac.run();
}

