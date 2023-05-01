#ifndef STATE_FUNCTIONS_H
#define STATE_FUNCTIONS_H
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522Extended.h>

#define PIR_Pin			12
#define BUZZER_Pin		13
#define LOCK_Pin		48

#define SDA_SS_Pin		53
#define RST_Pin			49

#define CARD_UID		"EB 4A 92 22"
#define TAG_UID 		"2A 1B 6F 81"

#define FREQ			400
#define alarmDuration	1000

enum StatesTransition
{
	TO_IDLE_STATE,
	TO_INPUT_STATE,
	TO_UNLOCK_STATE,
	TO_ALERT_STATE,
	TO_ADMIN_STATE
};
int i = 0x10;
#define ROWS 4
#define COLS 4

inline char keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

inline byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
  
inline Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
inline LiquidCrystal lcd(2, 3, 14, 15, 16, 17);
inline MFRC522 RFID(SDA_SS_Pin, RST_Pin);  // Create MFRC522 instance

inline bool motion_detected = false, lockState = true;
inline char key = NO_KEY;
inline String CORRECT_PASS = "1234";

inline int From_IdleState();
inline int From_InputState();
inline int From_UnlockState();
inline int From_AlertState();
inline int From_AdminState();

inline void unlockSolenoid() {
	if (lockState) {
		digitalWrite(LOCK_Pin, LOW);
		lockState = false;
	}
}

inline void lockSolenoid() {
	if (!lockState) {
		digitalWrite(LOCK_Pin, HIGH);
		lockState = true;
	}
}

inline bool validRFID() {
	// Look for new cards
	if (RFID.PICC_IsNewCardPresent() && RFID.PICC_ReadCardSerial()) {
		// Read the card ID
		String ReadID = "";

		for (byte i = 0; i < RFID.uid.size; i++) {
			ReadID += RFID.uid.uidByte[i] < 0x10 ? "0" : "";
			ReadID += String(RFID.uid.uidByte[i], 16);
		}
		RFID.PICC_HaltA();
		RFID.PCD_StopCrypto1();
		
		// Compare the card ID with the target ID
		if (ReadID == CARD_UID || ReadID == TAG_UID)
			return (true);
	}
	return (false);
}
#endif
