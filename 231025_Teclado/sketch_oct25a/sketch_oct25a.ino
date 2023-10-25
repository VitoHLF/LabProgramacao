/*  Teclado Matricial de Membrana
  Contém uma matriz de botões de pressão conectados. Tem conectores
de controle para cada linha e para cada coluna. O programa precisa 
colocar um sinal em um conjunto de conectores (das linhas ou das colunas)
e verificar se o sinal aparece aparece em algum conector do outro conjunto.
          ||||||||
*/

char teclado[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinhas[4] = {2,3,4,5};
byte pinosColunas[4] = {6,7,8,9};

int clickLinha, clickColuna;
unsigned long int iteracao;

void setup() {
  pinMode(pinosLinhas[0], OUTPUT);
  pinMode(pinosLinhas[1], OUTPUT);
  pinMode(pinosLinhas[2], OUTPUT);
  pinMode(pinosLinhas[3], OUTPUT);
  pinMode(pinosColunas[0], INPUT_PULLUP);
  pinMode(pinosColunas[1], INPUT_PULLUP);
  pinMode(pinosColunas[2], INPUT_PULLUP);
  pinMode(pinosColunas[3], INPUT_PULLUP);  

  Serial.begin(57600);
}

void loop() {
  for(int i=0; i<4; i++){
    digitalWrite(pinosLinhas[i], HIGH);
  }
  digitalWrite(pinosLinhas[iteracao%4], LOW);

  for(int i=0; i<4; i++){
    if(!digitalRead(pinosColunas[i]) && iteracao%4 == 0){
      Serial.print(teclado[0][i]);
      /* Serial.print(i+1);
      Serial.print(" x ");
      Serial.print(1);*/
      Serial.println(); 
    }
    if(!digitalRead(pinosColunas[i]) && iteracao%4 == 1){
      Serial.print(teclado[1][i]);
      /* Serial.print(i+1);
      Serial.print(" x ");
      Serial.print(2);*/
      Serial.println(); 
    }
    if(!digitalRead(pinosColunas[i]) && iteracao%4 == 2){
      Serial.print(teclado[2][i]);
      /* Serial.print(i+1);
      Serial.print(" x ");
      Serial.print(3);*/
      Serial.println();
    }
    if(!digitalRead(pinosColunas[i]) && iteracao%4 == 3){
      Serial.print(teclado[3][i]);
      /* Serial.print(i+1);
      Serial.print(" x ");
      Serial.print(4);*/
      Serial.println(); 
    }
  }

  iteracao++;
}
