// ---------------------------------------------------------------------------
// pBot Library - v1.0 - 12/03/2019
//
// AUTHOR/LICENSE:
// Created by Francesco A. Perrotti - faperrotti@hotmail.com
// Copyright 2014-2019 License: GNU General Public License v3
// http://www.gnu.org/licenses/
//
// Get the last version of this lib at:
// https://sourceforge.net/projects/arduino-libs/files
//
// DISCLAIMER:
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
// ---------------------------------------------------------------------------
//
// Esta biblioteca é parte do projeto de desenvolvimento de robôs móveis 
// desenvolvido por Francesco A. Perrotti para a Fatec Americana.
// Pode ser usada para fins comerciais ou pessoais livremente,
// apenas deixe citado o autor.
//

// Basic example of CircularBuffer class

#include <pCircBuff.h>

CircularBuffer cbuf;

// Structure to be used in buffer.
//
typedef struct{
  int number;
  char str[8];
} MyStruct;

// Add items to buffer
void addItems()
{
  MyStruct ms;
  
  for(int i=0; i<10; i++)
  {
    switch (i){
      case 0: strcpy(ms.str, "Uno");     break;
      case 1: strcpy(ms.str, "Bi");      break;
      case 2: strcpy(ms.str, "Tri");     break;
      case 3: strcpy(ms.str, "Tetra");   break;
      case 4: strcpy(ms.str, "Penta");   break;
      case 5: strcpy(ms.str, "Hexa");    break;
      case 6: strcpy(ms.str, "Hepta");   break;
      case 7: strcpy(ms.str, "Octopus"); break;
      case 8: strcpy(ms.str, "Nueve");   break;
      case 9: strcpy(ms.str, "Decup");   break;
    }
    ms.number= i+1;  
    cbuf.addItem((byte*)&ms);
  }
}

// Prints the retrieved item
//
void printStruct(MyStruct* ms)
{
  Serial.print(ms->number);
  Serial.print(": ");
  Serial.println(ms->str);
}

void setup() 
{
  Serial.begin(57600);
  cbuf.begin(10, sizeof(MyStruct));
}

#define lapse 333
ulong next= 0;

void loop() 
{
  // If the buffer is empty, fill the buffer
  if(cbuf.itemsCount()==0) 
  {
    addItems();
    Serial.println();
  }

  if(millis()>= next)
  {
    MyStruct ms;
    // Retrieve the next item
    cbuf.getFirst((byte*)&ms);
    
    // Print item
    printStruct(&ms);
    
    next= millis()+lapse;
  }
}
