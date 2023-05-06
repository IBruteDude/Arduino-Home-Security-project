#include "StateFunctions.h"

int From_UnlockState()
{
	// Initialize variables and LCD monitor

	unlockSolenoid();
	lcd.clear();
	lcd.print("Unlocked");

	// Wait until Exit key is pressed

	while(key != '*') {
		key = keypad.getKey();
		delay(50);
	}

	return TO_IDLE_STATE;
}
