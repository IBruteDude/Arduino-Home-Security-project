#include "StateFunctions.h"

void setup()
{
	lcd.begin(16, 2);
	lcd.print("Bismillah");
	pinMode(pirPin, INPUT_PULLUP);
	pinMode(buzzerPin, OUTPUT);
	// TODO: RFID tag and solenoid lock Setup
}
void loop()
{
	IdleState();
}