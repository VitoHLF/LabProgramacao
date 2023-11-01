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

// Hcsr04 class example.

#include <pHcsr04.h>

/**
 * 
 * Chame o método begin() para informar os pinos que serão usados e 
 * a unidade de distância (centimetros ou polegadas). 
 * O método hcDist() faz a leitura do sensor e retorna a distancia
 * na unidade selecionada.
 */

#define trigPin 2
#define echoPin 3

Hcsr04 hc;

void setup() 
{
  Serial.begin(57600);
  hc.begin(trigPin, echoPin, centimeter);
}

void loop() 
{
  int dist= hc.hcDist();
  if(dist<0)
    sprint("Fora de alcance ou erro de leitura.");
  else
    sprint2("Dist: ", dist);  
  sprint("\n");
  delay(500);
}
