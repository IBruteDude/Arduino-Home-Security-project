#include "StateFunctions.h"

int From_IdleState() {
	lcd.noDisplay();
	lockSolenoid();
	key = NO_KEY;

	while (key != '#') {
		// if (digitalRead(PIR_Pin) == LOW) {
		// 	lcd.display();
		// 	return TO_ALERT_STATE;
		// }
    	key = keypad.getKey();
    	delay(50);
	}
	return TO_INPUT_STATE;
}