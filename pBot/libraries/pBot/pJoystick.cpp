#include "pJoystick.h"

void JoyStick::begin(byte xAxisPin, byte yAxisPin, byte zButtonPin)
{
	PushButton::begin(zButtonPin, true);
	this->xAxisPin= xAxisPin;
	this->yAxisPin= yAxisPin;

  xAxisRef= analogRead(xAxisPin);
  yAxisRef= analogRead(yAxisPin);
  delayMicroseconds(3);
  xAxisRef= (xAxisRef+analogRead(xAxisPin))/2;
  yAxisRef= (yAxisRef+analogRead(yAxisPin))/2;
}

void JoyStick::axisConfig(int normalizeTo, byte tolerance, boolean zIgnoreXY)
{
  if(tolerance>0) this->tolerance= tolerance;
  this->zIgnoreXY= zIgnoreXY;

  if(normalizeTo)
  {
    scaleX= (long)normalizeTo*10000/xAxisRef;
    scaleY= (long)normalizeTo*10000/yAxisRef;
  }
}

void JoyStick::onButtonPressed()
{
	onZButtonPressed();
}

void JoyStick::onButtonReleased()
{
	onZButtonReleased();
}

int JoyStick::readXAxis()
{
  return ((analogRead(xAxisPin) - xAxisRef)*scaleX)/10000;
}

int JoyStick::readYAxis()
{
  return ((analogRead(yAxisPin) - yAxisRef)*scaleY)/10000;
}

boolean JoyStick::readZButton()
{
  return PushButton::read(); 
}

void JoyStick::run()
{
	PushButton::run();
  if(isPressed() && zIgnoreXY) return;

  int xVal= readXAxis();
  int yVal= readYAxis();
  
  if(abs(xVal)<=tolerance) xVal=0;
  if(abs(yVal)<=tolerance) yVal=0;

  if(abs(xVal-lastX)>=tolerance)
  {
    lastX= xVal;
    onXAxisChange(xVal);
  }

  if(abs(yVal-lastY)>=tolerance)
  {
    lastY= yVal;
    onYAxisChange(yVal);
  }
}

