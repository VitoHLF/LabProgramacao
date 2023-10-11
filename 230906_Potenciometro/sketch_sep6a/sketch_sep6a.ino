/*
Potenciometro:
  Componente que contém um resistor e um cursor que permite regular a resistência no pino de saída
Portas analógicas:
  O arduino tem 6 portas analógicas (A0 até A5) com resolução de 10 bits (1024 níveis) para leitura
*/

#define pinPot A0
#define led1 3
#define led2 4
#define led3 5
#define led4 6

void setup() {
  //Serial.begin(57600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  int val = analogRead(pinPot);
  //Serial.println(val);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  if(val<256){
    digitalWrite(led1, HIGH);
  }
  if(val>=256 && val<512){
    digitalWrite(led2, HIGH);
  }
  if(val>=512 && val<768){
    digitalWrite(led3, HIGH);
  }
  if(val>=768){
    digitalWrite(led4, HIGH);
  }
  delay(500);
}
