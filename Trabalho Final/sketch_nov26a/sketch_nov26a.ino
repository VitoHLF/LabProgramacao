#include <Servo.h>

 //Joystick
#define VRx A0
#define VRy A1
#define pinBotao 3

//Motor de Passo
#define pinMot1 8
#define pinMot2 9
#define pinMot3 10
#define pinMot4 11

#define delayMotTime 5

//Servo
#define pinServo 2 
Servo sv;

#define lapse 50
#define pinDebug 13

bool isOn = false; 
int valX = 0, valY = 0, zeroX, zeroY, valServo=50;
bool estadoLed = false, lastBotao = false;
unsigned long next = 0;

void setup() {
  Serial.begin(57600);
  pinMode(pinDebug, OUTPUT);
  sv.attach(pinServo);
  sv.write(50);

  zeroX = analogRead(VRx);
  zeroY = analogRead(VRy);

  pinMode(pinMot1, OUTPUT);
  pinMode(pinMot2, OUTPUT);
  pinMode(pinMot3, OUTPUT);
  pinMode(pinMot4, OUTPUT);

  pinMode(pinBotao, INPUT_PULLUP);
}

void loop() {
  valX = analogRead(VRx) - zeroX;
  valY = analogRead(VRy) - zeroY;
  boolean estadoBotao = !digitalRead(pinBotao);

  if(millis()>=next){
    if(estadoBotao!= lastBotao){
      lastBotao = estadoBotao;
      if(estadoBotao){
        estadoLed = !estadoLed;
        digitalWrite(pinDebug, estadoLed);
      }
    }

    if(valY<-300 && valServo>50){
      valServo-=2;
      sv.write(valServo);
    }if(valY>300 && valServo<110){
      valServo+=2;
      sv.write(valServo);
    }


    /* Serial.println(valX);
    Serial.println(valY); */
    Serial.println(valServo);
    next+=lapse;
  }

  if(valX<-300) stepClockwise();
  if(valX>300) stepCounterClock();

}


void stepClockwise(){
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
  delay(delayMotTime);
  digitalWrite(pinMot1, LOW);
  digitalWrite(pinMot2, LOW);
  digitalWrite(pinMot3, LOW);
  digitalWrite(pinMot4, LOW);
}

void stepCounterClock(){
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
  delay(delayMotTime);
  digitalWrite(pinMot1, LOW);
  digitalWrite(pinMot2, LOW);
  digitalWrite(pinMot3, LOW);
  digitalWrite(pinMot4, LOW);
}
