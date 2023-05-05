#include "StateFunctions.h"

int From_UnlockState()
{
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
