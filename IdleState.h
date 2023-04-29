#include "StateFunctions.h"

int From_IdleState() {
	lcd.noDisplay();
	while (keypad.getKey() != '#') {
		if (digitalRead(pirPin) == HIGH) {
			return TO_ALERT_STATE;
		}
	}
	return TO_INPUT_STATE;
}