#define lapse 500

int led[4] = {2,3,4,5};
unsigned long next;
unsigned long current;
boolean status = false;


void setup() {
  for(int i=0; i<4; i++){
    pinMode(led[i], OUTPUT);
  }
  next = 0;
  current = 0;
  for(int i =0; i<4; i++){
    digitalWrite(led[i], 1);
  }
}

void loop() {
  if(millis() >= next){
    digitalWrite(led[current], 1);
    /*for(int i=0; i<4; i++){
      if(i != current) digitalWrite(led[i], 0);
    }*/
    current++;
    if(current > 3) current=0;
    next= millis()+lapse;
  }
}
