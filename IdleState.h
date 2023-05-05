#include "StateFunctions.h"

int From_IdleState() {
	lcd.noDisplay();
	lockSolenoid();
	key = NO_KEY;

	// Wait in a loop until user presses Start '#'

	while (key != '#') {
		key = keypad.getKey();
		motion_detected = digitalRead(PIR_Pin);
		// Check if the sensor detected motion

		if (motion_detected == HIGH) {
			lcd.display();
			return TO_ALERT_STATE;
		}
		delay(50);
	}
	// Program started go to use input

	return TO_INPUT_STATE;
}