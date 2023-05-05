#include "StateFunctions.h"

#define ALARM_FREQ		1000
#define alarmDuration	1000

int From_AlertState()
{
	tone(BUZZER_Pin, ALARM_FREQ);
	lcd.clear();
	lcd.print("Access Denied");
	if (motion_detected == true) {
		lcd.setCursor(0, 1);
		lcd.print("INTRUDER");
	}

	// Wait until valid UID is detected, and when true return to Admin State
	while (!validRFID_Read) {
		validRFID_Read = validRFID();
		key = keypad.getKey();
		delay(50);
	}

	return TO_ADMIN_STATE;
}