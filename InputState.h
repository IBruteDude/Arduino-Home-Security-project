#include "StateFunctions.h"


#define PASS_LEN 4
#define idleDuration 5000
#define Pause 3000

int From_InputState()
{
	unsigned long startingTime = millis();
	String password;
	int wrongAttempts = 0;

	lcd.display();
	lcd.clear();
	lcd.print("Enter Password:");
	while (true)
	{
    lcd.clear();
	  lcd.print("Enter Password:");
		// The main waiting loop
		key = NO_KEY;
    while (key == NO_KEY) {
			key = keypad.getKey();
      validRFID_Read = validRFID();
			if (millis() - startingTime > idleDuration)
				return TO_IDLE_STATE;
			// if (digitalRead(PIR_Pin) == HIGH) {
			// 	return TO_ALERT_STATE;
			// }
			if (key == 'A') {
				return TO_ADMIN_STATE;
			}
		}

		if (password.length() == CORRECT_PASS.length()) {
			lcd.clear();
			if (password == CORRECT_PASS) {
				// Set to unlocked state
				lcd.print("Correct Pass");
				wrongAttempts = 0;
				delay(Pause);
				return TO_UNLOCK_STATE;
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
					delay(Pause);
					lcd.clear();
					password = "";
				}
			}
		} else {
			password += key;
			lcd.setCursor(password.length(), 1);
			lcd.print('*');
		}
	}
}