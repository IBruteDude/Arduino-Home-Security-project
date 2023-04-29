#include "StateFunctions.h"

int From_AlertState()
{
	tone(buzzerPin, FREQ);
	lcd.clear();
	lcd.print("Access Denied");
	if (motion_detected == true) {
		lcd.setCursor(0, 1);
		lcd.print("INTRUDER");
	}

	// Check for RFID reader, and when true return TO_ADMIN
}