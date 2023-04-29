#include "StateFunctions.h"


#define PASS_LEN 4
#define idleDuration 30000
#define retryPause 3000

int From_InputState()
{
	unsigned long startingTime = millis(), upTime;
	String password;
	int wrongAttempts = 0;

	lcd.display();
	lcd.print("Enter");
	while (true)
	{
		while (keypad.getKey() == NO_KEY) {
			if (millis() - startingTime > idleDuration)
				return (0);
		}

		if (password.length() == CORRECT_PASS.length()) {
			lcd.clear();
			if (password == CORRECT_PASS) {
				
				lcd.print("Correct Pass");
				wrongAttempts = 0;
				// Unlock the solenoid lock
				lockState = true;
			} else {
				lcd.print("Incorrect Pass");
				wrongAttempts++;
				// Set to alert state and require Administration approval
				if (wrongAttempts >= 3) {
					return TO_ALERT_STATE;
				} else {	
					// Set LCD to retrial state
					lcd.setCursor(0, 1);
					lcd.print(3 - wrongAttempts);
					lcd.setCursor(1, 1);
					lcd.print(" attempts left");
					delay(retryPause);
					lcd.clear();
					password = "";
				}
			}
		}
	}
}