/* MOTOR DE PASSO
  Motor de alta precisão que é controlado por uma sequência de pulsos elétricos onde cada pulso faz com que gire um "passo".
  A quantidade de passos por volta determina a precisão do motor.  

*/

#include <Stepper.h>

#define delayMotTime 5

#define pinMot1 8
#define pinMot2 9
#define pinMot3 10
#define pinMot4 11

#define pinBotBrnc 2
#define pinBotVerm 3

void setup() {
  // put your setup code here, to run once:
  pinMode(pinMot1, OUTPUT);
  pinMode(pinMot2, OUTPUT);
  pinMode(pinMot3, OUTPUT);
  pinMode(pinMot4, OUTPUT);

  pinMode(pinBotBrnc, INPUT_PULLUP);
  pinMode(pinBotVerm, INPUT_PULLUP);
}

void loop() {
  
  if(!digitalRead(pinBotBrnc)){
    counterClock();
  }else if(!digitalRead(pinBotVerm)){
    clockwise();
  }else{
    digitalWrite(pinMot1, LOW);
    digitalWrite(pinMot2, LOW);
    digitalWrite(pinMot3, LOW);
    digitalWrite(pinMot4, LOW);  
  }
}

void clockwise(){
  delay(delayMotTime);
  digitalWrite(pinMot1, HIGH);
  digitalWrite(pinMot2, HIGH);
  digitalWrite(pinMot4, LOW);
  delay(delayMotTime);
  digitalWrite(pinMot1, LOW);
  digitalWrite(pinMot2, HIGH);
  digitalWrite(pinMot3, HIGH);
  delay(delayMotTime);
  digitalWrite(pinMot2, LOW);
  digitalWrite(pinMot3, HIGH);
  digitalWrite(pinMot4, HIGH);
  delay(delayMotTime);
  digitalWrite(pinMot3, LOW);
  digitalWrite(pinMot4, HIGH);
  digitalWrite(pinMot1, HIGH);
}

void counterClock(){
  delay(delayMotTime);
  digitalWrite(pinMot1, HIGH);
  digitalWrite(pinMot2, HIGH);
  digitalWrite(pinMot4, LOW);
  delay(delayMotTime);
  digitalWrite(pinMot3, LOW);
  digitalWrite(pinMot4, HIGH);
  digitalWrite(pinMot1, HIGH);
  delay(delayMotTime);
  digitalWrite(pinMot2, LOW);
  digitalWrite(pinMot3, HIGH);
  digitalWrite(pinMot4, HIGH);
  delay(delayMotTime);
  digitalWrite(pinMot1, LOW);
  digitalWrite(pinMot2, HIGH);
  digitalWrite(pinMot3, HIGH);
}

void rotate360(){
  for(int i=0; i<512; i++){
    clockwise();
  }
  digitalWrite(pinMot4, LOW);
  digitalWrite(pinMot1, LOW);
}