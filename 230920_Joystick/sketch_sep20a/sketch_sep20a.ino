/*
Joystick c/ botão
  Combina 2 potenciômetros posicionados em cruz, um sistema de molas para manter o cursos centralizado 
e um botão de pressão.
*/

#define pinoR 11
#define pinoG 10
#define pinoB 9

#define VRx A0
#define VRy A1
#define pinBotao 3
#define lapse 50

  int zeroX, zeroY;
  int valX = 0;
  int valY = 0;
  bool estadoLed = false;
  bool lastBotao = false;
  unsigned long next = 0;

void setup() {
  pinMode(pinBotao, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(pinoR, OUTPUT);
  pinMode(pinoG, OUTPUT);
  pinMode(pinoB, OUTPUT);
  /* zeroX = analogRead(VRx);
  zeroY = analogRead(VRy);
 */
  digitalWrite(pinoR, HIGH);
  digitalWrite(pinoG, HIGH);
  digitalWrite(pinoB, HIGH);
}

void loop() {
  valX = analogRead(VRx);// - zeroX;
  valY = analogRead(VRy);// - zeroY;
  boolean estadoBotao = !digitalRead(pinBotao);

  if(millis()>=next){
    if(estadoBotao!= lastBotao){
      lastBotao = estadoBotao;
      if(estadoBotao) estadoLed = !estadoLed;
    }
  }

  if(estadoLed){
    analogWrite(pinoR, valX/4);
    analogWrite(pinoB, valY/4);
  }else{
    digitalWrite(pinoR, HIGH);
    digitalWrite(pinoG, HIGH);
    digitalWrite(pinoB, HIGH);
  }
  //digitalWrite(13, estadoLed);
}
