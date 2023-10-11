#define botao 3
#define led 13
#define lapse 50

boolean anteriorBotao = false;
boolean estadoLed = false;
unsigned long next = 0;

void setup() {
  pinMode(botao, INPUT_PULLUP); //SETA O PINO COMO SAIDA COM O MODO DE PULLUP DA PLACA
  pinMode(led, OUTPUT);
}

void loop() {
  boolean estadoBotao = !digitalRead(botao);

  if(millis() >= next){
    if(estadoBotao != anteriorBotao){
      anteriorBotao = estadoBotao;
      if(estadoBotao) estadoLed = !estadoLed;
      digitalWrite(led, estadoLed);
    }
    next+=lapse;
  }
}
