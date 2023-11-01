// ---------------------------------------------------------------------------
// pBot Library - v1.05 - 10/03/2019
//
// AUTHOR/LICENSE:
// Created by Francesco A. Perrotti - faperrotti@hotmail.com
// Copyright 2014 License: GNU General Public License v3
// http://www.gnu.org/licenses/
//
// Download
// https://sourceforge.net/projects/arduino-libs/files/
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

/*
  Ultimamente as baterias Li-Ion estão bastante populares porque são recarregáveis, 
  têm baixo custo e alta potência. São facilmente encontradas no formato de pilhas 
  no padrão 18650 e 14650. As pilhas tem tensão nominal de 3.7 volts, mas quando 
  estão completamente carregadas chegam a fornecer 4.1 volts. São bastante 
  práticas e uma boa opção para a alimentação de robôs. O problema dessa tecnologia 
  é que as pilhas não podem ser completamente descarregadas. Se a voltagem chegar 
  abaixo de 2.7 volts elas podem perder a capacidade de recarga.

  Depois de perder uma boa quantidade de pilhas, resolvi criar uma maneira de 
  permitir que o robô monitore a carga das baterias e avise quando é hora de 
  recarregar. A maneira mais simples de monitorar a carga das baterias é com
  um divisor de tensão que reduza a tensão total do pacote de baterias para 
  os 5 volts das entradas analógicas do arduino. Como o divisor de tensão 
  tem a saída proporcional à entrada, conforme a carga vai baixando, a saída
  do divisor baixa na mesma proporção.

  IMPORTANTE: Um divisor de tensão é um circuito extremamente simples de 
  fazer, envolve apenas dois resistores, mas é preciso tomar o cuidado de
  não usar resistores de valores baixos. As entradas analógicas do arduino 
  não precisam e não suportam alta corrente. Quanto maior o valor dos 
  resistores, menos corrente eles deixam passar e menor o impacto no 
  consumo de energia. 

  Além do divisor de tensão, o circuito descrito no arquivo pBattSense.png 
  prevê um led de aviso do nível de carga e uma saída para um interruptor
  geral do sistema. Está configurado para entrada de 12.3 volts, que 
  corresponde à tensão máxima fornecida por 3 pilhas em série. Para outras 
  voltagens de entrada, basta substituir os resistores R1 e R2. É fácil achar 
  calculadoras on-line para divisores de tensão, mas para facilitar segue 
  abaixo uma tabela com sugestão de valores para R1 e R2:

   8.2 volts (2 pilhas): 
      R1: 680 K   R2: 1 M

  12.3 volts (3 pilhas): 
      R1: 1 M     R2: 680 K
      R1: 680 K   R2: 470 K

  16.4 volts (4 pilhas): 
      R1: 900 K   R2: 390 K
      R1: 2.2 M   R2: 900 K
      R1: 1 M     R2: 420 K
      R1: 680 K   R2: 280 K
*/

#ifndef pBattSense_h
#define pBattSense_h
#include "pGlobals.h"

//#define BS_VOUT_REF      3.3
#define BS_VOUT_REF      5.0
#define BS_NO_BATT_LED   255

class BatterySense
{
public:
  float lastVin;
  boolean battHalf= false;
  boolean battLow = false;

  BatterySense(){}
  void begin(float maxVin, float maxVout, float minVin, byte sensePin, byte ledPin= BS_NO_BATT_LED, float vOutRef= BS_VOUT_REF);
  float readVIn();
  void run();

private:
  float constVin;
  int lowVal, halfVal;
	byte sensePin, ledPin;
};



#endif