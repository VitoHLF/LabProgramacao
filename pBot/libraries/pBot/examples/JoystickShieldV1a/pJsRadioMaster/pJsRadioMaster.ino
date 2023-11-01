#include <pJsRadio.h>

uint8_t pipeIn [6]= "0Rf24";
uint8_t pipeOut[6]= "1Rf24";

#define NORMALIZE_TO  100   // XY axis values ranges from -100 to 100
#define TOLERANCE     3     // Minimum axis variation to trigger event (after normalize)
#define Z_IGNORE_XY   true  // Ignore XY events when button Z is pressed
#define AUTO_SEND     true  // Auto send joy stick events

const char btNames[7][7] = {
  "up",
  "left",
  "down",
  "righ",
  "config",
  "reset",
  "Z" };
  
class JsMaster: public JsRadioMaster
{
  public:
  long txCount= 0;
  long rxCount= 0;
  
  JsMaster():JsRadioMaster(){};
  
  void begin()
  {
    JsRadioMaster::begin(pipeIn, pipeOut, RF24_1MBPS, AUTO_SEND);
    axisConfig(NORMALIZE_TO, TOLERANCE, Z_IGNORE_XY);
  }
  
  void onJsPacketRead(TJsPacket *pack)
  {
    rxCount++;
  }

  void onJsPacketSent(TJsPacket *pack)
  {
    txCount++;
    sprint3("TX[", txCount, "]: ");
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
};

JsMaster jsm;

void setup() 
{
  Serial.begin(57600);
  jsm.begin();

  Serial.println("\nIniciando loop\n");
}

void loop() 
{
  jsm.run();
}
