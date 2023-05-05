#include "StateFunctions.h"


#define PASS_LEN 		4
#define idleDuration 	30000
#define Pause 			3000
#define CLICK_FREQ		1400
#define WRONG_FREQ		1000

int From_InputState()
{
	wrongAttempts = 0;
	password = "";
	lcd.display();
	lcd.blink();
	lcd.clear();
	lcd.print("Enter Password:");

	while (true)
	{
		key = NO_KEY;
		startingTime = millis();
		// Wait in a loop until user presses a key
		
		while (key == NO_KEY) {
			key = keypad.getKey();
			validRFID_Read = validRFID();
			motion_detected = digitalRead(PIR_Pin);
			// Check for a valid RFID
			
			if (validRFID_Read) {
				return TO_ADMIN_STATE;
			}
			// Check if idle duration is exceeded
			
			if (millis() - startingTime > idleDuration)
				return TO_IDLE_STATE;
			// Check if the sensor detected motion

			if (motion_detected == HIGH)
				return TO_ALERT_STATE;
			delay(50);
		}

		// Key pressed and recorded
		
		password += key;
		tone(BUZZER_Pin, CLICK_FREQ, 150);
		lcd.setCursor(password.length() - 1, 1);
		lcd.print('*');

		if (password.length() == CORRECT_PASS.length()) {
			lcd.clear();
			if (password == CORRECT_PASS) {
				// Set to unlocked state
				
				lcd.print("Correct Pass");
				delay(Pause);
				return TO_UNLOCK_STATE;
			} else if (wrongAttempts < 3) {
				// Warn the user and retry

				lcd.print("Incorrect Pass");
				wrongAttempts++;
				lcd.setCursor(0, 1);
				lcd.print(3 - wrongAttempts);
				lcd.setCursor(1, 1);
				lcd.print(" attempts left");
				tone(BUZZER_Pin, WRONG_FREQ , 500);
				delay(Pause);
				lcd.clear();
				lcd.print("Enter Password:");
				password = "";
			} else {
				// Wrong password set the alarm
				
				return TO_ALERT_STATE;
			}
		}
	}
}