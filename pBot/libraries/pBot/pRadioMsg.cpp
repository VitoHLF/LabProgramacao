#include "pRadioMsg.h"

//////////////////////////////////////////////////////////////////////////////
///
///  RadioMessage
///
void RadioMessage::begin(byte *pipeIn, byte *pipeOut, TDatarate rate)
{
  RF24::begin();
  setDataRate(rate);
  setAutoAck(true);
  setRetries(2,15);
  enableDynamicPayloads();          
  openWritingPipe(pipeOut);
  openReadingPipe(1, pipeIn);
  rxMode();    
}

  // Em teste
void RadioMessage::begin(byte *pipeIn, TDatarate rate, byte myNodeID)
{
  RF24::begin();
  setDataRate(rate);
  setAutoAck(true);
  setRetries(2,15);
  enableDynamicPayloads();          
}

void RadioMessage::addNode(byte *nodePipe, byte nodeID)
{

}

THeader* RadioMessage::makeHeader(THeader* head, byte msgID, byte payloadSize)
{
	nextSerial++;
	head->msgID= msgID;
	head->serialN= nextSerial;
	head->paySize= payloadSize;
	return head;
}


TRadioMsg* RadioMessage::makeMessage(TRadioMsg* msg, byte msgID, byte payloadSize, void* payload)
{
	makeHeader(&msg->head, msgID, payloadSize);
	if(payloadSize && payload)
		memcpy(msg->buff, payload, min(PAYLOAD_MAX_LEN, payloadSize));

	return msg;
}

int RadioMessage::sendMessage(TRadioMsg* msg)
{
	int result= writeBuff(msg, min(sizeof(TRadioMsg), msg->head.paySize + sizeof(THeader)));
  return result<0? result: result-sizeof(THeader);
}

int RadioMessage::readMessage(TRadioMsg* msg)
{
	if(!available()) return rdErr_NothingToRead;
	int result= readBuff(msg, sizeof(TRadioMsg));
  return result<0? result: result-sizeof(THeader);
}

byte RadioMessage::getMsgID(TRadioMsg* msg)
{
  return msg->head.msgID;
}

byte RadioMessage::getMsgPaySize(TRadioMsg* msg)
{
  return msg->head.paySize;
}

void* RadioMessage::getMsgPayload(TRadioMsg* msg)
{
  return msg->buff;
}

byte RadioMessage::copyMsgPayload(TRadioMsg* msg, void* destination)
{
  memcpy(destination, msg->buff, msg->head.paySize);
  return msg->head.paySize;
}

int RadioMessage::readBuff(void* buff, byte maxSize)
{
    if (!available()) return rdErr_NothingToRead;

    byte len = getDynamicPayloadSize();
    if(!len) return rdErr_ZeroLen;
    len= min(len, maxSize);

    read(buff, len);
    return len;
}

int RadioMessage::writeBuff(void* buff, byte sizeBuff)
{
    byte len= min(sizeBuff, 32);
    txMode();
    write(buff, len);
    rxMode();
    return len;
} 

void RadioMessage::run()
{
  if(available())
  {
    TRadioMsg msg;
    readMessage(&msg);
    onIncommingMsg(&msg);
  }
}

