#include "StateFunctions.h"

#include "IdleState.h"
#include "InputState.h"
#include "UnlockState.h"
#include "AlertState.h"
#include "AdminState.h"

int Next_Program_State;

void setup()
{
	lcd.begin(16, 2);
	lcd.print("Bismillah");
	pinMode(pirPin, INPUT_PULLUP);
	pinMode(buzzerPin, OUTPUT);
	// TODO: RFID tag and solenoid lock Setup


	Next_Program_State = 0;
}
void loop()
{
	switch(Next_Program_State)
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