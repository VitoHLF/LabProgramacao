#include "pPushButton.h"

/////////////////////////////////////////////////////////////////////////
///
/// PushButton
///

PushButton::PushButton()
{
	owner= NULL;
}

PushButton::PushButton(byte btID, ButtonOwner *owner)
{
	this->btID= btID;
	this->owner= owner;
}

void PushButton::begin(byte buttonPin, boolean pullUp)
{
	btPin= buttonPin;
	this->pullUp= pullUp;

	if(pullUp) pinMode(btPin, INPUT_PULLUP);
	else		  pinMode(btPin, INPUT);

	lastVal= digitalRead(btPin);
	pressed= lastVal;
	if(pullUp) pressed= !pressed;
}

boolean PushButton::read()
{
	return pullUp? !digitalRead(btPin): digitalRead(btPin);
}

boolean PushButton::run()
{
	if(digitalRead(btPin) != lastVal)
	{
		lastVal= !lastVal;
		pressed= !pressed;
 		if(pressed) {
			if(owner) 
				owner->buttonPressed(btID);
			else 
				onButtonPressed();
		}
		else {
			if(owner) 
				owner->buttonReleased(btID);
			else
				onButtonReleased();
		}
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////
///
/// PushButtonArray
///

PushButtonArray::PushButtonArray(): ButtonOwner()
{
	this->owner= NULL;
}

PushButtonArray::PushButtonArray(ButtonOwner *owner): ButtonOwner()
{
	this->owner= owner;
}

boolean PushButtonArray::begin(byte maxButtons)
{
  this->maxButtons= maxButtons;
  but= (PushButton**)calloc(maxButtons, sizeof(PushButton*));
  return but != NULL;
}

int PushButtonArray::addButton(byte buttonPin, boolean pullUp)
{
	if(btCount>=maxButtons) return 255;
	but[btCount]= new PushButton(btCount, owner?owner:this);
	if(!but[btCount]) return -1;

	but[btCount]->begin(buttonPin, pullUp);
	btCount++;
	return btCount-1;
}

void PushButtonArray::run()
{
	if(!btCount) return;
	but[ctRun]->run();
	circularInc(ctRun, btCount);

	//for (int i = 0; i < btCount; ++i) 
		//but[i]->run();
}

boolean PushButtonArray::isPressed(byte btID)
{
	return but[btID]->isPressed();
}



void PushButtonArray::buttonPressed(byte btID)
{
	onButtonPressed(btID);
}

void PushButtonArray::buttonReleased(byte btID)
{
	onButtonReleased(btID);
}
