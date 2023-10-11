#define botao1 2
#define botao2 3
#define led 13



void setup() {
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  if(!digitalRead(botao1)){
    digitalWrite(led, 1);
  }

  if(!digitalRead(botao2)){
    digitalWrite(led, 0);
  }
}
