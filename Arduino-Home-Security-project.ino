#include "StateFunctions.h"

#include "IdleState.h"
#include "InputState.h"
#include "UnlockState.h"
#include "AlertState.h"
#include "AdminState.h"


int Next_Program_State;

void setup()
{
	// Initialise arduino pin modes
	pinMode(PIR_Pin, INPUT);
	pinMode(BUZZER_Pin, OUTPUT);
	pinMode(LOCK_Pin, OUTPUT);

	lcd.begin(16, 2);		// Initialise LCD rows & columns
	lcd.print("Bismillah"); // بنسمي الله
	SPI.begin();			// Initialise SPI bus
	RFID.PCD_Init();		// Initialise MFRC522

	// Initialise the Programs state
	Next_Program_State = TO_IDLE_STATE;
	motion_detected = false;
	noTone(BUZZER_Pin);
	lockSolenoid();
}
void loop()
{
// digitalWrite(LOCK_Pin, HIGH);
// delay(1000)  ;
// digitalWrite(LOCK_Pin, LOW);
// delay(1000)  ;	// switch(Next_Program_State)
	switch (Next_Program_State)
  {
	case TO_IDLE_STATE:
		Next_Program_State = From_IdleState();
		break;
	case TO_INPUT_STATE:
		Next_Program_State = From_InputState();
		break;
	case TO_UNLOCK_STATE:
		Next_Program_State = From_UnlockState();
		break;
	case TO_ALERT_STATE:
		Next_Program_State = From_AlertState();
		break;
	case TO_ADMIN_STATE:
		Next_Program_State = From_AdminState();
		break;
	}
}