#include "StateFunctions.h"

int From_AdminState()
{
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
		while(key == NO_KEY)
			key = keypad.getKey();
		switch(key)
		{
		case 'A':
			// Change password
			
			return TO_ADMIN_STATE;
		case 'B':
			// Turn Off alarm functionality
			
			return TO_ADMIN_STATE;
		case 'C':
			// Turn Off lock functionality
			
			return TO_ADMIN_STATE;
		case '*':
			return TO_IDLE_STATE;
		}
	}
}