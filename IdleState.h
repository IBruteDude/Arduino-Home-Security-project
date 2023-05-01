#include "StateFunctions.h"

int From_IdleState() {
  lcd.noDisplay();
  key = NO_KEY;
  digitalWrite(BUZZER_Pin, LOW);
	while (key != '#') {
		// if (digitalRead(PIR_Pin) == HIGH) {
		// 	return TO_ALERT_STATE;
		// }
    key = keypad.getKey();
    // delay(100);
	}
	return TO_INPUT_STATE;
}