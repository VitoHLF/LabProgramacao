#ifndef pJsRadio_h
#define pJsRadio_h

#include "pRadioMsg.h"
#include "pJs_ShieldV1a.h"

/*
__AVR_ATmega168__ ATmega 168  Arduino Decimilia and older
__AVR_ATmega328P__  ATmega 328P Arduino Duemilanove and Uno
__AVR_ATmega1280__  ATmega 1280 Arduino Mega
__AVR_ATmega2560__  ATmega 2560 Arduino Mega 2560
__AVR_ATmega32U4__  ATmega 32U4 Arduino Leonardo
__SAM3X8E__ AT91SAM3X8E Arduino Due
*/    

#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
    // Arduino Mega
    #define RADIO_CE_PIN    9
    #define RADIO_CS_PIN   53
    // mosi: 51
    // miso: 50
    // sck : 52
#else 
    // Arduino UNO/Nano
    #define RADIO_CE_PIN    9
    #define RADIO_CS_PIN   10
    // mosi: 11
    // miso: 12
    // sck : 13
#endif

typedef struct 
{
  byte msgID;
  int param;
}
TJsPacket;

// msgID
#define msg_JS_BUTTON_PRESSED    1
#define msg_JS_BUTTON_RELEASED   2
#define msg_JS_X_AXIS_CHANGE     3
#define msg_JS_Y_AXIS_CHANGE     4
#define msg_JS_LAST_JS_MSG_ID    msg_JS_Y_AXIS_CHANGE

/// Base class for JsRadioMaster and JsRadioSlave. Implements
/// a basic protocol based on TJsPacket struct to exchange messages 
/// between joy stick board (JsRadioMaster) and the receiving 
/// node (JsRadioSlave).
///
class JoyStickRadio: public RadioMessage
{
public:  
  /// Constructor
  /// @param cePin arduino pin conected to CE radio pin. 
  /// @param csPin arduino pin conected to CS radio pin. 
  JoyStickRadio(int cePin, int csPin): RadioMessage(cePin, csPin){}

  /// Check for incomming messages. Call once per loop.
  ///
  void run();

  /// Populate a packet.
  ///
  TJsPacket* makeJsPacket(TJsPacket *pack, byte msgID, int param);
  
  /// Send a packet to other node.
  /// @param pack Packet to send.
  ///
  int sendJsPacket(TJsPacket *pack);

  /// Read a packet from other node.
  /// @param pack Packet readed.
  ///
  int readJsPacket(TJsPacket *pack);

protected:
  // Events. Override to capture.
  virtual void onJsPacketSent(TJsPacket *pack){};
  virtual void onJsPacketRead(TJsPacket *pack){};

  // dont override
  virtual void onPacketTx(TJsPacket *pack);
  virtual void onPacketRx(TJsPacket *pack);
};


class JsRadioMaster: public JoyStickRadio, public JoyStickShield
{
public:  
  /* Constructor
  */
  JsRadioMaster(): JoyStickShield(), JoyStickRadio(RADIO_CE_PIN, RADIO_CS_PIN){}

  /* Call before any method
  */
  void begin(uint8_t* pipeIn, uint8_t* pipeOut, TDatarate rate, boolean autoSendEvents= false);

  /* Call once per loop
  */
  void run();

protected:
  // Events. Override to capture.
  virtual void jsButtonPressed(byte btID){}
  virtual void jsButtonReleased(byte btID){}
  virtual void jsXAxisChange(int xVal){}
  virtual void jsYAxisChange(int yVal){}

private:
  void onButtonPressed(byte btID);
  void onButtonReleased(byte btID);
  void onXAxisChange(int xVal);
  void onYAxisChange(int yVal);

  void onPacketRx(TJsPacket *pack);
  void onPacketTx(TJsPacket *pack);

  boolean autoSend;
};

class JsRadioSlave: public JoyStickRadio
{
public:  
  JsRadioSlave(int cePin, int csPin): JoyStickRadio(cePin, csPin){}
  void begin(byte *pipeIn, byte *pipeOut, TDatarate rate);

protected:
  // Events. Override to capture.
  virtual void onButtonPressed(byte btID){}
  virtual void onButtonReleased(byte btID){}
  virtual void onXAxisChange(int xVal){}
  virtual void onYAxisChange(int yVal){}

  // Unprotected, dont override
  virtual void onPacketRx(TJsPacket *pack);
  virtual void onPacketTx(TJsPacket *pack);
};

#endif