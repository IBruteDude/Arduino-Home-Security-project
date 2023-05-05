#include "StateFunctions.h"

#define ALARM_FREQ		1000
#define alarmDuration	1000

int From_AlertState()
{
	lcd.clear();
	lcd.print("Access Denied");
	tone(BUZZER_Pin, ALARM_FREQ);
	validRFID_Read = false;

	if (motion_detected == true) {
		lcd.setCursor(0, 1);
		lcd.print("INTRUDER");
	}

	// Wait until valid RFID is detected

	while (!validRFID_Read) {
		validRFID_Read = validRFID();
		key = keypad.getKey();
		delay(50);
	}

	// Go to admin mode

	return TO_ADMIN_STATE;
}