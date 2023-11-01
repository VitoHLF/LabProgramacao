#include "pCircBuff.h"

CircularBuffer::~CircularBuffer()
{
  if(buff)
    free(buff);
}

boolean CircularBuffer::begin(byte items, byte itemSize)
{
  this->itemSize= itemSize;
  this->items= items;
  clear();

  buffSize= items*itemSize;
  buff= (byte*)malloc(buffSize);
  return buff != NULL;
}

void CircularBuffer::clear()
{
   firstItem= 0;
   nextPos= 0;
   count= 0;
}

boolean CircularBuffer::addItem(void* item)
{
  if(count>=items) return false;
  memcpy(&buff[nextPos], item, itemSize);
  nextPos= (byte)(((uint)nextPos+itemSize) % buffSize);
  count++;
  return true;
}

void* CircularBuffer::getFirst(void* item)
{
  if(!count) return NULL;

  memcpy(item, &buff[firstItem], itemSize);
  firstItem= (firstItem+itemSize) % buffSize;
  count--;
  return item;
}

void* CircularBuffer::getLast(void* item)
{
  if(!count) return NULL;

  nextPos= ((int)nextPos+buffSize-itemSize) % buffSize;
  memcpy(item, &buff[nextPos], itemSize);

  count--;
  return item;
}

void* CircularBuffer::checkLast()
{
  if(!count) return NULL;

  return &buff[((int)nextPos+buffSize-itemSize) % buffSize];
}

void* CircularBuffer::checkFirst()
{
  if(!count) return NULL;

  return &buff[firstItem];
}

byte CircularBuffer::itemsCount()
{
  return count;
}
