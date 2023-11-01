#include "pJsRadio.h"

//////////////////////////////////////////////////////////////////////////////
///
///  JsRadioSlave
///

void JsRadioSlave::begin(byte *pipeIn, byte *pipeOut, TDatarate rate)
{
	JoyStickRadio:: begin(pipeIn, pipeOut, rate);
}

void JsRadioSlave::onPacketTx(TJsPacket *pack)
{ 
	onJsPacketSent(pack); 
}

void JsRadioSlave::onPacketRx(TJsPacket *pack)
{
   switch(pack->msgID)
   {
      case msg_JS_BUTTON_PRESSED: 	
			onButtonPressed(pack->param); break;

      case msg_JS_BUTTON_RELEASED:	
			onButtonReleased(pack->param); break;

      case msg_JS_X_AXIS_CHANGE: 		
			onXAxisChange(pack->param); break;

      case msg_JS_Y_AXIS_CHANGE:		
			onYAxisChange(pack->param); break;
   }
  	onJsPacketRead(pack);
}

