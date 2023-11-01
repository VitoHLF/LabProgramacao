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

#ifndef pHcsr04_h
#define pHcsr04_h
#include "pGlobals.h"

/**
 * @file pHcsr04.h
 *
 * Driver for ultrasonic distance modules compatibles with HCSR-04. 
 * Definitions and declaration of Hcsr04, HcsrAuto and HcsrArray classes.
 *
 * Driver para módulos de medição de distâncias por ultrassom do tipo HCSR-04.
 * Definições e declaração das classes Hcsr04, HcsrAuto e HcsrArray.
 */


// Timeout para as leituras (em microsegundos)
#define hc_TimeOut 18000

#define hcErr_Timeout     -1
#define hcErr_Hardware    -2
#define hcErr_ArrayIsFull -3
#define hcErr_NoMemory    -4

// Se o eco demorar mais que hc_TimeOut, o obstáculo 
// é considerado fora de alcance. Na prática estabelece 
// a distancia máxima que será medida pelo sensor. 
//
// Abaixo uma tabela com alguns valores.
// 24000: 408cm
// 22000: 374cm
// 20000: 340cm
// 18000: 306cm
//
// Dica importante: Se mesmo tentando criar todas as condições ideais para
// a leitura do sensor vc não conseguir ler medidas próximas de 4 metros,
// talvez seja uma boa ideia diminuir o timeout. Vc vai continuar não 
// conseguindo ler distâncias próximas a 4 metros, mas pelo menos a função
// de leitura vai retornar mais rápido e o programa vai fluir melhor.

typedef enum{centimeter=0, inch} DistUnit;

//////////////////////////////////////////////////////////////////////////
// class Hcsr04: classe para controlar um sensor de distância 
//               HC-SR04 com um ou dois pinos. Os sinais Trig e 
// Echo podem compartilhar o mesmo pino no arduino. Nesse caso é preciso 
// por um resistor de pulldown entre o pino que será usado e o GND do arduino, 
// 100 Kohm é suficiente.
//
class Hcsr04{
  public:
    /** 
     * Construtor da classe 
     */
    Hcsr04();

    /** 
     * Inicialização. Deve ser chamado antes de qualquer outro método.
     *
     * @param triggerPin Pino conectado ao Trigger do módulo
     * @param echoPin Pino conectado ao Echo do módulo
     * @param unit Unidade de distancia. 
     * @note É possível usar o mesmo pino do arduino para as funções trigger
     * e echo do sensor. Nesse caso o pino deve ser aterrado através de um 
     * resistor de pelo menos 100kohms (PULL-DOWN). A classe prevê essa 
     * situação e faz o processamento necessário. Para isso basta indicar o 
     * mesmo pino nos parâmetros triggerPin e echoPin.
     */
    void begin(byte triggerPin, byte echoPin, DistUnit unit= centimeter);


    /** 
     * Lê o sensor e retorna a distância lida na unidade selecionada
     *
     * @param tries Se a leitura falhar e tries>1, serão feitas novas 
     *              tentativas até o total indicado em tries ou até obter 
     *              uma leitura válida.
     * @return Se a leitura foi feita com sucesso retorna a distancia lida. 
     *         Caso contrário retorna um valor menor que zero que 
     *         corresponde ao código de erro.
     *
     */
    int hcDist(byte tries=1);

    /** 
     * Lê o sensor e retorna o tempo do eco em microsegundos.
     *
     * @return Se a leitura foi feita com sucesso retorna o tempo do eco. 
     * Caso contrário retorna um valor menor que zero que corresponde 
     * ao código de erro.
     *
     */
    long ultraSonicRead();

  private:
    byte triggerPin, echoPin;
    DistUnit unit;
};

//////////////////////////////////////////////////////////////////////////
// class HcsrAuto: Automatiza a leitura de um sensor de distância do tipo 
//                 HC-SR04. 
//
class HcsrAuto: public Hcsr04
{
public:
  int lastDist;
  
  HcsrAuto():Hcsr04(){}

  /** 
  * Inicialização. Deve ser chamado antes de qualquer outro método.
  *
  * @param triggerPin Pino conectado ao Trigger do módulo
  * @param echoPin Pino conectado ao Echo do módulo
  * @param unit Unidade de distancia (centimeter ou inch). 
  * @note É possível usar o mesmo pino do arduino para as funções trigger
  * e echo do sensor. Nesse caso o pino deve ser aterrado através de um 
  * resistor de pelo menos 100kohms (PULL-DOWN). A classe prevê essa 
  * situação e faz o processamento necessário. Para isso basta indicar o 
  * mesmo pino nos parâmetros triggerPin e echoPin.
  */
  void begin(byte triggerPin, byte echoPin, DistUnit unit= centimeter);

  /**
  * Inicia a medição automática. 
  * @param milliseconds Tempo entre leituras em milissegundos.
  */
  void hcStart(uint milliseconds);

  /**
  * Para a medição automática. 
  */
  void hcStop();

  /**
  * Deve ser chamado a cada iteração do loop principal. Este método verifica o 
  * tempo decorrido desde a última leitura e quando necessário realiza nova 
  * leitura. O evento onHcRead() é disparado sempre que uma nova leitura é feita.
  * @return Retorna true quando é feita uma nova leitura e false quando não.
  * O valor lido fica armazenado no atributo público lastDist. 
  */
  boolean run();

  // From Hcsr04
  //
  // int hcDist(byte tries=1);
  // long ultraSonicRead();

protected:
  /**
  * Evento disparado sempre que uma nova leitura é feita. Pode ser capturado por 
  * alguma classe descendente.
  */
  virtual void onHcRead(int dist){}
  
private:
  ulong nextRead=0;
  uint lapse=0;
};


// Intervalo (tempo) default entre leituras para o array de 
// sensores em milisegundos. O intervalo pode ser alterado 
// chamando setPatrolTime().
//
#define hc_PatrolLapse   100

class HcsrItem: public Hcsr04
{
public:
  int lastDist=0;

  HcsrItem():Hcsr04(){}

  int readNow(byte tries=1)
  {
    return lastDist= hcDist(tries);
  }
};

//////////////////////////////////////////////////////////////////////////
// class HcsrArray: Classe para controlar um array de sensores de distância 
//                  do tipo HC-SR04.


class HcsrArray
{
public:
  int lastDist;

  /** 
   * Construtor da classe 
   */
  HcsrArray(){}
  ~HcsrArray();

  /** 
   * Inicialização
   */
  boolean begin(byte maxSensors, DistUnit unit= centimeter);

  /** 
   * Adiciona um sensor ao array de sensores.
   *
   * @param triggerPin Pino conectado ao Trigger do módulo adicionado
   * @param echoPin Pino conectado ao Echo do módulo adicionado
   * @param angle Angulo do módulo em relação à frente do objeto onde está instalado.
   * @param offset Distancia do modulo até a borda do objeto onde está 
   * instalado. Esta distância é subtraída da distância lida .
   * 
   * @return ID do módulo. Usado para futura referencia ao módulo.
   */
  int addHcSensor(byte triggerPin, byte echoPin);

  /** 
   * Lê o sensor indicado
   *
   * @param hcID ID do sensor que será lido
   *
   * @return Distancia lida ou código de erro.
   */
  int readHcDist(byte hcID, byte tries=1);

  /** 
   * Lê todos os sensores no array
   *
   * @return A quantidade de sensores lidos com sucesso
   */
  int readHcArray(byte tries=1);

  /** 
   * Ativa o modo patrulha. Neste modo todos os sensores são lidos 
   * em sequência em intervalos regulares de tempo. O tempo entre a 
   * leitura de um sensor e a leitura do próximo é informado no parâmetro
   * milliseconds.
   */
  void patrolModeOn(uint milliseconds);

  /** 
   * Desativa o modo patrulha. 
   */
  void patrolModeOff();

  /** 
   * Verifica o tempo e faz as leituras automáticas.
   *
   * @return True se foi feita uma nova leitura, false se não.
   */
  boolean run();

  /** 
   * Retorna a última distancia lida
   *
   * @return Última distancia lida 
   */
  int getLastDist();

  /** 
   * Retorna a última distancia lida para o sensor indicado
   *
   * @param hcID ID do sensor
   *
   * @return Última distancia lida para o sensor indicado por hcID
   */
  int getLastDist(byte hcID);

  /** 
   * Retorna o ID do sensor onde foi feita a última leitura
   *
   * @return ID do sensor onde foi feita a última leitura
   */
  byte lastHcID();

  /** 
   * Retorna a quantidade de sensores adicionados ao array
   *
   * @return Quantidade de sensores adicionados ao array
   */
  byte hcCount(){ return count; }

  boolean isPatrolDone(){ return patrol_done; }

  int getMinDist();
  int getMaxDist();
  
protected:   
  // Override to capture
  virtual void onNextHcRead(byte hcID, int dist){}
  virtual void onPatrolDone(){}

private:
  HcsrItem** hc;
  DistUnit unit;
  byte maxSensors, count, patrolCount, lastHc;
  boolean patrol_on= false,
          patrol_done= false;
  unsigned int lapse;
  unsigned long nextRead;
};

#endif

