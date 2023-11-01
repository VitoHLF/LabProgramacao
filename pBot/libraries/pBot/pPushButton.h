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

#ifndef pPushButton_h
#define pPushButton_h

#include "pGlobals.h"
#include "pOwners.h"

// class PushButton: Drive a single push button.
//
class PushButton
{
public:
	// btID: Button's ID. Used by PushButtonArray class.
	byte btID=0;

	// To drive one button, use this constructor
	//
	PushButton();

	// Used by PushButtonArray class.
	//
	PushButton(byte btID, ButtonOwner *owner);

	// Call before any method.
	//
	void begin(byte buttonPin, boolean pullUp=true);

	// Call at least once per loop. Returns true if the button has 
	// changed its status since the last call or false if it has 
	// remained the same state.
	//
	boolean run();

	// Returns true if button is pressed or false if not.
	//
	boolean isPressed(){ return pressed; }

	// Make a new read and return true if button is pressed or false if not.
	//
	boolean read();


protected:
	// Events for use in descending classes. 
	// These events are not triggered if the 
	// constructor with owner is used.
	//
	virtual void onButtonPressed(){}
	virtual void onButtonReleased(){}

private:
	byte btPin;
	boolean pullUp, lastVal;
	boolean pressed;
	ButtonOwner *owner;
};

class PushButtonArray: private ButtonOwner
{
public:
	byte btCount=0;
	PushButton** but;

	// construtores
	PushButtonArray();
	PushButtonArray(ButtonOwner *owner);

	// inicialização
	boolean begin(byte maxButtons);
	int addButton(byte buttonPin, boolean pullUp=true);

	// operação
	void run();
	boolean isPressed(byte btID);

protected:
	// Eventos para uso em classes descendentes.
	// Estes eventos não são disparados se for usado 
	// o construtor com owner.
	virtual void onButtonPressed(byte btID){}
	virtual void onButtonReleased(byte btID){}

private:
	byte maxButtons;
  	void buttonPressed(byte btID);
  	void buttonReleased(byte btID);
	ButtonOwner *owner;
	byte ctRun=0;
};

#endif

