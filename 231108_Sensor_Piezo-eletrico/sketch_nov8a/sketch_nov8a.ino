/* Sensor Piezo-elétrico
  É um transdutor, ou seja, converte uma forma de energia em outra forma de energia
e faz isso nos dois sentidos.
  Pode ser usado como sensor ou como atuador. Quando recebe um sinal elétrico ele vibra.
Se o sinal for modulado em uma frequencia específica, vai vibrar nessa frequência podendo
inclusive tocar notas musicais(atuador).
  Mas o contrário também é verdade, se sofrer vibração, torção ou impacto ele produz um
sinal elétrico com intensidade proporcional.

vermelho -> pino digital
preto -> gnd

  tone(pino, frequência);
  noTone(pino);
 */

#define pinoSensor 13

#define C4 261
#define CS4 277
#define D4 293
#define DS4 311
#define E4 330
#define F4 349
#define FS4 370
#define G4 392
#define GS4 415
#define A4 440
#define AS4 466
#define B4 493
#define C5 523
#define CS5 554


void setup() {
  pinMode(pinoSensor, OUTPUT);
}

void loop() {

  //Cruel Angel Thesis
  nota(C4, 500);
  nota(DS4, 500);
  nota(F4, 375);
  nota(DS4, 375);
  nota(F4, 250);
  nota(F4, 250);
  nota(F4, 250);
  nota(AS4, 250);
  nota(GS4, 250);
  nota(G4, 125);
  nota(F4, 250);
  nota(G4, 625); 

  nota(G4, 500);
  nota(AS4, 500);
  nota(C5, 375);
  nota(F4, 375);
  nota(DS4, 250);
  nota(AS4, 500);
  nota(G4, 250);
  nota(AS4, 250);
  nota(AS4, 375);
  nota(C5, 625);

}

void nota(int frequencia, int tempo){
  tone(pinoSensor, frequencia);
  delay(tempo);
  noTone(pinoSensor);
}