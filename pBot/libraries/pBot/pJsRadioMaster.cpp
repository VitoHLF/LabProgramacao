#include "pJsRadio.h"

//////////////////////////////////////////////////////////////////////////////
///
///  JsRadioMaster
///

void JsRadioMaster::begin(uint8_t* pipeIn, uint8_t* pipeOut, TDatarate rate, boolean autoSendEvents)
{
	JoyStickShield::begin();
	JoyStickRadio::begin(pipeIn, pipeOut, rate);
	autoSend= autoSendEvents;
}

void JsRadioMaster::onButtonPressed(byte btID)
{
	if(autoSend) 
	{
		TJsPacket pack= { msg_JS_BUTTON_PRESSED, (int) btID };
		sendJsPacket(&pack);
	}
	jsButtonPressed(btID);
}

void JsRadioMaster::onButtonReleased(byte btID)
{
	if(autoSend) 
	{
		TJsPacket pack= { msg_JS_BUTTON_RELEASED, (int) btID };
		sendJsPacket(&pack);
	}

	jsButtonReleased(btID);
}

void JsRadioMaster::onXAxisChange(int xVal)
{
	if(autoSend) 
	{
		TJsPacket pack= { msg_JS_X_AXIS_CHANGE, xVal };
		sendJsPacket(&pack);
	}
	jsXAxisChange(xVal);
}

void JsRadioMaster::onYAxisChange(int yVal)
{
	if(autoSend) 
	{
		TJsPacket pack= { msg_JS_Y_AXIS_CHANGE, yVal };
		sendJsPacket(&pack);
	}

	jsYAxisChange(yVal);
}

void JsRadioMaster::onPacketTx(TJsPacket *pack)
{
  	onJsPacketSent(pack);
}

void JsRadioMaster::onPacketRx(TJsPacket *pack)
{
  	onJsPacketRead(pack);
}

void JsRadioMaster::run()
{
	JoyStickShield::run();
	JoyStickRadio::run();
}

