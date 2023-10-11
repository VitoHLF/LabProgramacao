/*
Servo Motor
  Motor elétrico com um sistema de engrenagens e um circuito que permite
posicionar em um ângulo especifico. Existem com capacidade de giro de 180 graus
e de 360 graus. O sistema de engrenagens proporciona um torque elevado.

Fios:
-Marrom: GND
-Vermelho: 5V
-Laranja: pino digital

biblioteca: <Servo.h>
*/
#include <Servo.h>

#define pinPotenciometro A0
#define pinoServo 3
#define lapse 50

Servo sv; //instância da classe servo
unsigned long next = 0;

void setup() {
  Serial.begin(57600);
  sv.attach(pinoServo);
  sv.write(0);
}

void loop() {
  int valPotenciometro = analogRead(pinPotenciometro) / 5.68;

  Serial.println(valPotenciometro);

  if(millis() >= next){
    sv.write(valPotenciometro);
    next+=lapse;
  }
}
