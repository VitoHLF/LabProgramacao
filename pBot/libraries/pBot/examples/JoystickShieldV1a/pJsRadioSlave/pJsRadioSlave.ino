#include <pJsRadio.h>

#define CE_PIN    9
#define CS_PIN   10

uint8_t pipeIn [6]= "1Rf24";
uint8_t pipeOut[6]= "0Rf24";

const char btNames[7][7] = {
  "up",
  "left",
  "down",
  "righ",
  "config",
  "reset",
  "Z" };
  
class JsSlave: public JsRadioSlave
{
  public:
  long rxCount= 0, 
       txCount= 0;

  JsSlave():JsRadioSlave(CE_PIN, CS_PIN){};
  
  void begin()
  {
    JsRadioSlave::begin(pipeIn, pipeOut, RF24_1MBPS);
  }
  
  void onJsPacketRead(TJsPacket *pack)
  {
    rxCount++;
    sprint3("RX[", rxCount, "]: ");
    switch(pack->msgID)
    {
      case msg_JS_BUTTON_PRESSED:
        sprint3("Button ", btNames[pack->param], " pressed\n");
        break;
      case msg_JS_BUTTON_RELEASED:
        sprint3("Button ", btNames[pack->param], " released\n");
        break;
      case msg_JS_X_AXIS_CHANGE:
        sprint3("X axis: ", pack->param, "\n");
        break;
      case msg_JS_Y_AXIS_CHANGE:
        sprint3("Y axis: ", pack->param, "\n");
        break;
    }
  }

  void onJsPacketSent(TJsPacket *pack)
  {
    txCount++;
  }
};

JsSlave jss;

void setup() 
{
  Serial.begin(57600);
  jss.begin();

  Serial.println("\nIniciando loop\n");
}

void loop() 
{
  jss.run();
}
