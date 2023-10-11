#define pinoLed 13
#define lapse 1000

unsigned long next;
unsigned long count;
boolean status = false;

void setup() {
  Serial.begin(57600);
  pinMode(pinoLed, OUTPUT);
  next = 0;
  count = 0;
}

void loop() {
  if(millis() >= next)
  {
    Serial.println(count);
    count= 0;
    
    next= millis() + lapse;
  }  
  count++;
}
