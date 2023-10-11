/* Sensor de Distância por ultrassom HCSR04
Emite uma rajada de pulsos em ultrassom e recebe o eco de obstáculos à frente.
Pelo tempo entre a rajada e o eco é possível calcular a distância do obstáculo.
Pode medir distâncias de 3cm até 3m.
Pinagem:
  -Vcc
  -Trigger: Pino de saída (digital)
  -Echo: Pino de entrada (digital)
  -Gnd

  Disparo:
digitalWrite(pinTrig, LOW);
delayMicroseconds(2);
digitalWrite(pinTrig, HIGH);
delayMicroseconds(10);
unsigned long tempo = pulsein(pinEcho, HIGH);
int cm = tempo*1717/100000;
 */
#define pinTrig 7
#define pinEcho 8

unsigned long tempo;
int distmm;

void setup() {
  Serial.begin(57600);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void loop() {
  
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  tempo = pulseIn(pinEcho, HIGH);
  distmm = tempo*1717/10000;

  Serial.println(distmm);
  delay(200);
}
