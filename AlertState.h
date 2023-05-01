#include "StateFunctions.h"

int From_AlertState()
{
	tone(BUZZER_Pin, FREQ);
	lcd.clear();
	lcd.print("Access Denied");
	if (motion_detected == true) {
		lcd.setCursor(0, 1);
		lcd.print("INTRUDER");
	}

	// Wait until valid UID is detected, and when true return to Admin State
	while (!validRFID() || keypad.getKey() != 'A');

	return TO_ADMIN_STATE;
}