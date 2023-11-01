#define axisX A0
#define axisY A1

#define buttonY 2
#define buttonB 3
#define buttonA 4
#define buttonX 5
#define buttonStart 6
#define buttonSelect 7
#define buttonJS 8

#define lapse 50

int valX = 0;
int valY = 0;
unsigned long next=0;

void setup() {
  pinMode(buttonY, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonX, INPUT_PULLUP);
  pinMode(buttonStart, INPUT_PULLUP);
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonJS, INPUT_PULLUP);

  Serial.begin(57600);
}

void loop() {
  valX = analogRead(axisX);// - zeroX;
  valY = analogRead(axisY);// - zeroY;

  if(millis()>=next){
    if(!digitalRead(buttonY)){
      Serial.println("Y");
    }
    if(!digitalRead(buttonA)){
      Serial.println("A");
    }
    if(!digitalRead(buttonX)){
      Serial.println("X");
    }
    if(!digitalRead(buttonB)){
      Serial.println("B");
    }
    if(!digitalRead(buttonStart)){
      Serial.println("Start");
    }
    if(!digitalRead(buttonSelect)){
      Serial.println("Select");
    }
    if(!digitalRead(buttonJS)){
      Serial.println("JS click");
    }
    Serial.print(valX);
    Serial.println();
    Serial.print(valY);
    Serial.println();
    next+=lapse;
  }
}
