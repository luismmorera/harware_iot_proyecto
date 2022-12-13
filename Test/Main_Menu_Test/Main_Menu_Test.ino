#include "BetaFit_Hardware.h"

volatile int ISRCounter = 0;
int counter = 0;

void setup()
{
	pinMode(D6_PIN, INPUT_PULLUP);
	Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(D6_PIN), debounceCount, FALLING);
}

void loop()
{
	if (counter != ISRCounter)
	{
		counter = ISRCounter;
		Serial.println(counter);
	}
}

void debounceCount()
{
	ISRCounter++;
}