#include "StateFunctions.h"

int From_AdminState()
{
	// Initialize variables and LCD monitor

	noTone(BUZZER_Pin);
	motion_detected = false;
	unlockSolenoid();

	lcd.clear();
	lcd.print("ADMIN: options");
	lcd.setCursor(0, 1);
	lcd.print("-A -B -C '*'");

	while (true)
	{
		key = NO_KEY;
		// Wait in a loop until user presses a key

		while(key == NO_KEY) {
			key = keypad.getKey();
			delay(50);
		}

		switch(key)
		{
		case 'A':
			// Change password
			
			break;
		case 'B':
			// Turn Off alarm functionality
			
			break;
		case 'C':
			// Turn Off lock functionality
			
			break;
		case '*':
			return TO_IDLE_STATE;
		}
	}
}