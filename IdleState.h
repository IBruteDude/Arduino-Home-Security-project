#include "StateFunctions.h"

int From_IdleState() {
  key = NO_KEY;
	lcd.noDisplay();
	while (key != '#') {
		if (digitalRead(PIR_Pin) == HIGH) {
			return TO_ALERT_STATE;
		}
    key = keypad.getKey();
	}
	return TO_INPUT_STATE;
}