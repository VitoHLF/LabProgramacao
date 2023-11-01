/*
	Original code from the Tone Library by Brett Hagman

	Adapted and Optimized by WilliamK @ Wusik Dot Com (c) 2010
	http://arduino.wusik.com

	Compact 8 Bit Timer (uses Timer2)

	See Timer2.h for instructions

*/

#include "pTimer2.h"

#define MAX_MICROS_LAPSE   16400
#define MAX_MICROS_TIME    (16400UL*65535UL)			// 1'077'788'610	~18 min

//#define MAX_MICROS_LAPSE   16446
//#define MAX_MICROS_TIME    (16446UL*65535UL)			// 1'077'788'610	~18 min

typedef void (*voidFunc)();

voidFunc _timerEvent= NULL;
boolean  _inTimer   = false;
TimerRoot*  _tmr;
uint laps=0, lapsCt=0;
ulong _overlaps=0;


ISR(TIMER2_COMPA_vect)
{
	if(lapsCt)
	{
		lapsCt--;
		return;
	}

   if(_inTimer) 
   {
  		_overlaps++;
  		return;
   }
  
   _inTimer= true;

   _tmr->trigEvent();
   lapsCt= laps-1;

  	_inTimer= false;
} 

// ------------------------------------------------------------------------------------------- //

Timer2::Timer2():TimerRoot()
{
  _tmr= this;
}

Timer2::Timer2(TimerOwner* owner):TimerRoot(owner)
{
  _tmr= this;
}

Timer2::Timer2(voidFunction externFunction):TimerRoot(externFunction)
{
  _tmr= this;
}

Timer2::~Timer2()
{
  stop();
}


ulong Timer2::overlaps()
{
	return _overlaps;
}

void Timer2::startMicros(ulong microseconds)
{
	if(microseconds>MAX_MICROS_TIME)
	{
		Serial.println("\nTimer2 interval too long.");
		return;
	}

	float mc;
	laps = 0;

	do{
		laps++;
		mc = (float)microseconds/laps;
	} while(mc>MAX_MICROS_LAPSE);

	lapsCt= laps-1;
	startF((float)1000000/mc);
}

void Timer2::startMillis(ulong milliseconds)
{
	startMicros(milliseconds*1000);
}


// ------------------------------------------------------------------------------------------- //
void Timer2::startF(float frequency)
{
	stop();

   TCCR2A = 0;
   TCCR2B = 0;
   bitWrite(TCCR2A, WGM21, 1);
   bitWrite(TCCR2B, CS20, 1);

	uint32_t ocr = F_CPU / frequency - 1;
	uint8_t prescalarbits = 0b001;

	if (ocr > 255)
	{
		ocr = F_CPU / frequency / 8 - 1;
		prescalarbits = 0b010;

		if (ocr > 255)
		{
			ocr = F_CPU / frequency / 32 - 1;
			prescalarbits = 0b011;
		}

		if (ocr > 255)
		{
			ocr = F_CPU / frequency / 64 - 1;
			prescalarbits = 0b100;

			if (ocr > 255)
			{
				ocr = F_CPU / frequency / 128 - 1;
				prescalarbits = 0b101;
			}

			if (ocr > 255)
			{
				ocr = F_CPU / frequency / 256 - 1;
				prescalarbits = 0b110;
				
				if (ocr > 255)
				{
					ocr = F_CPU / frequency / 1024 - 1;
					prescalarbits = 0b111;

					if (ocr > 255)
					{
						stop();
						Serial.println("Timer2 Error!");
						Serial.flush();
						return;
					}
				}
			}
		}
	}

	TCCR2B = prescalarbits;
	OCR2A = ocr;
	bitWrite(TIMSK2, OCIE2A, 1);
}

// ------------------------------------------------------------------------------------------- //
void Timer2::stop()
{
	bitWrite(TIMSK2, OCIE2A, 0);
	TCCR2A = (1 << WGM20);
	TCCR2B = (TCCR2B & 0b11111000) | (1 << CS22);
	OCR2A = 0;
}