/*
PWM - Pulse Width Modulation
  Tecnica utilizada para emular uma saida analógica em pinos digitais.
Consiste em ligar e desligar o pino em um intervalo de tempo bem curto.
Modulando o tempo que o pino fica ligado em relação ao tempo desligado, 
é possivel gerar qualquer voltagem de saída entre 0 e 5V .
  O arduíno tem esse recurso via hardware em pinos específicos. 
  No caso do arduino uno são 6 pinos marcados com o símbolo ~.

  analogWrite(pinoPWM, Nível de Saída);
  Nível: 0 - 255

Led RGB
  São 3 leds encapsulados juntos, um vermelho, um verde e um azul.
  Existem 2 tipos: com o positivo comum e com o negativo comum.
  Variando a intensidade de cada led é possível gerar qualquer cor do sistema RGB.
*/

#define pinoB 9
#define pinoG 10
#define pinoR 11

//R -> B

#define lapse 50

int valR = 0;
int valG = 0;
int valB = 0;
unsigned long next=0;

bool stateR = true;
bool stateG = false;
bool stateB = false;

void setup() {
  pinMode(pinoR, OUTPUT);
  pinMode(pinoG, OUTPUT);
  pinMode(pinoB, OUTPUT);
}

void loop() {  
  if(millis()>=next){
    
    if(stateR){
      valR--;
    }else valR++;
    
    if(stateG){
      valG--;
    }else valG++;
    
    if(stateB){
      valB--;
    }else valB++;

    analogWrite(pinoR, valR);
    analogWrite(pinoG, valG);
    analogWrite(pinoB, valB);

    if(valR>=255){
      valR = 255;
    }
    if(valG>=255){
      valG = 255;
    }
    if(valB>=255){
      valB = 255;
    }    

    if(valR<=0) valR = 0;
    if(valG<=0) valG = 0;
    if(valB<=0) valB = 0;

    next+=lapse;
  }
}
