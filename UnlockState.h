#include "StateFunctions.h"

int From_UnlockState()
{
	unlockSolenoid();
	lcd.clear();
	lcd.print("Unlocked");
	while (keypad.getKey() != '*')
		;
	return TO_IDLE_STATE;
}
