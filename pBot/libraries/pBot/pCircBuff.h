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

#ifndef pCircBuff_h
#define pCircBuff_h

#include <pGlobals.h>

//------------------------------------------------------------------------------------
// CircularBuffer- Implements a circular buffer based on array of bytes. 
//						 Descending classes can associate any struct to buffer. 
// The buffer is dynamically allocated by the begin() method . 
//
class CircularBuffer
{
  public:
	CircularBuffer(){};
	~CircularBuffer();

	// Aloca o buffer.
	// Retorna false se não há memória suficiente,
	// ou true se não houve erro
	//
   boolean begin(byte items, byte itemSize);

   // Adiciona um item no final do buffer
   //
	boolean addItem(void* item);

	// Retorna e remove o primeiro item 
	//
	void* getFirst(void* item);

	// Retorna e remove o último item 
	//
	void* getLast(void* item);

	// Limpa o buffer
	//
	void clear();

	// Quantidade atual de itens no buffer
	//
	byte itemsCount();

	// Retorna um ponteiro para o último item adicionado.
	// Não modifica o buffer.
	//
	void* checkLast();

	// Retorna um ponteiro para o primeiro item adicionado.
	// Não modifica o buffer.
	//
	void* checkFirst();

  private:
	byte items, itemSize, count;
	uint firstItem, nextPos, buffSize;
	byte* buff;
};

#endif
