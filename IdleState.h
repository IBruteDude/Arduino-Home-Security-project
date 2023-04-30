#include "StateFunctions.h"

int From_IdleState() {
	lcd.noDisplay();
	while (keypad.getKey() != '#') {
		if (digitalRead(PIR_Pin) == HIGH) {
			return TO_ALERT_STATE;
		}
	}
	return TO_INPUT_STATE;
}