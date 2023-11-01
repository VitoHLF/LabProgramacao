#include "pJsRadio.h"

//////////////////////////////////////////////////////////////////////////////
///
///  JoyStickRadio
///

TJsPacket* JoyStickRadio::makeJsPacket(TJsPacket *pack, byte msgID, int param)
{
	pack->msgID= msgID;
	pack->param= param;
	return pack;
}

int JoyStickRadio::sendJsPacket(TJsPacket *pack)
{
	TRadioMsg msg;
	int result= sendMessage(makeMessage(&msg, pack->msgID, sizeof(TJsPacket), pack));
	
	if(result>=0)
    	onPacketTx(pack);

    return result;
}

int JoyStickRadio::readJsPacket(TJsPacket *pack)
{
	if(!messageWaiting()) return rdErr_NothingToRead;

	TRadioMsg msg;
	int result= readMessage(&msg);
	
	if(result>=0)
	{
  		copyMsgPayload(&msg, pack);
    	onPacketRx(pack);
	}

   return result;
}

void JoyStickRadio::onPacketTx(TJsPacket *pack)
{ 
	onJsPacketSent(pack); 
}

void JoyStickRadio::onPacketRx(TJsPacket *pack)
{ 
	onJsPacketRead(pack); 
}

void JoyStickRadio::run()
{
  if(messageWaiting())
  {
    TJsPacket pack;
  	 readJsPacket(&pack);
  }
}


