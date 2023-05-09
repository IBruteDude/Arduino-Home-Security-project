/**
 * Included Arduino libraries
 */
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522Extended.h>
/**
 * Pins and constant values used in the program
 */
#define PIR_Pin			12
#define BUZZER_Pin		13
#define LOCK_Pin		48
#define SDA_SS_Pin		53
#define RST_Pin			49

#define CARD_UID		" EB 4A 92 22"
#define TAG_UID 		" 2A 1B 6F 81"
#define idleDuration 	30000
#define Pause 			3000
#define GOOD_FREQ		1400
#define BAD_FREQ		1000
#define alarmDuration	1000
enum StatesTransition
{
	TO_IDLE_STATE,
	TO_INPUT_STATE,
	TO_UNLOCK_STATE,
	TO_ALERT_STATE,
	TO_ADMIN_STATE
};
#define ROWS 4
#define COLS 4
char keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};
char rowPins[ROWS] = {4, 5, 6, 7};
char colPins[COLS] = {8, 9, 10, 11};
/** 
 * Global variables shared in the program
 */
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(2, 3, 14, 15, 16, 17);
MFRC522 RFID(SDA_SS_Pin, RST_Pin);  // Create MFRC522 instance
/**
 * Local variables used inside functions
 */
bool motion_detected = false, lockState = true, validRFID_Read = false;
char key = NO_KEY;
String CORRECT_PASS = "1234", password;
String UID;
unsigned long startingTime;
int i, wrongAttempts, Next_Program_State;
/**
 * States' function prototypes
 */
int From_IdleState();
int From_InputState();
int From_UnlockState();
int From_AlertState();
int From_AdminState();
/**
 * Useful functions
 */
void unlockSolenoid();
void lockSolenoid();
bool validRFID();





void setup()
{
	// Initialize arduino pin modes

	pinMode(PIR_Pin, INPUT_PULLUP);
	pinMode(BUZZER_Pin, OUTPUT);
	pinMode(LOCK_Pin, OUTPUT);

	lcd.begin(16, 2);		// Initialize LCD rows & columns
	lcd.print("Bismillah"); // بنسمي الله
	SPI.begin();			// Initialize SPI bus
	RFID.PCD_Init();		// Initialize RFID device

	// Initialize the Program's state

	Next_Program_State = TO_IDLE_STATE;
}

void loop()
{
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





inline void unlockSolenoid() {
	// if (lockState)
	{
		digitalWrite(LOCK_Pin, LOW);
		lockState = false;
	}
}
inline void lockSolenoid() {
	// if (!lockState)
	{
		digitalWrite(LOCK_Pin, HIGH);
		lockState = true;
	}
}
bool validRFID() {
	// Check if a card is detected
	
	if (!RFID.PICC_IsNewCardPresent()) 
		return false;
	if (!RFID.PICC_ReadCardSerial()) 
		return false;
	UID = "";

	// Read the card UID

	for (i = 0; i < RFID.uid.size; i++) {
		 UID.concat(String(RFID.uid.uidByte[i] < 0x10 ? " 0" : " "));
		 UID.concat(String(RFID.uid.uidByte[i], HEX));
	}
	UID.toUpperCase();

	// Check for UID you want to give access 
	
	if (UID == CARD_UID) {
		return true;
	}
	return false;
}





int From_IdleState()
{
	// Initialize variables and LCD monitor
	lcd.noDisplay();
	lockSolenoid();
	key = NO_KEY;
	// Wait in a loop until user presses Start '#'
	while (key != '#') {
		key = keypad.getKey();
		motion_detected = digitalRead(PIR_Pin);
		// Check if the sensor detected motion
		if (motion_detected == LOW) // LOW indicates detection
			return TO_ALERT_STATE;
		delay(50);
	}
	// Program started go to use input
	return TO_INPUT_STATE;
}

int From_InputState()
{
	// Initialize variables and LCD monitor
	wrongAttempts = 0;
	lcd.display();
	lcd.clear();
	lcd.print("Enter Password:");
	lcd.setCursor(0, 1);
	lcd.blink();
	password = "";
	while (true)
	{
		key = NO_KEY;
		startingTime = millis();
		// Wait in a loop until user presses a key
		while (key == NO_KEY) {
			key = keypad.getKey();
			validRFID_Read = validRFID();
			motion_detected = digitalRead(PIR_Pin);
			// Check for a valid RFID	
			if (validRFID_Read)
				return TO_ADMIN_STATE;
			// Check if idle duration is exceeded
			if (millis() - startingTime > idleDuration)
				return TO_IDLE_STATE;
			// Check if the sensor detected motion
			if (motion_detected == LOW) // LOW indicates detection
				return TO_ALERT_STATE;
			delay(50);
		}
		// Key pressed and recorded
		password += key;
		tone(BUZZER_Pin, GOOD_FREQ, 150);
		lcd.setCursor(password.length() - 1, 1);
		lcd.print('*');
		if (password.length() == CORRECT_PASS.length()) {
			lcd.noBlink();
			lcd.clear();
			if (password == CORRECT_PASS) {
				// Set to unlocked state
				lcd.print("Correct Pass");
				delay(Pause);
				return TO_UNLOCK_STATE;
			} else if (wrongAttempts < 3) {
				// Warn the user and retry
				lcd.print("Incorrect Pass");
				wrongAttempts++;
				lcd.setCursor(0, 1);
				lcd.print(3 - wrongAttempts);
				lcd.setCursor(1, 1);
				lcd.print(" attempts left");
				tone(BUZZER_Pin, BAD_FREQ , 500);
				delay(Pause);
				lcd.clear();
				lcd.print("Enter Password:");
				lcd.setCursor(0, 1);
				lcd.blink();
				password = "";
			} else {
				// Wrong password set the alarm	
				return TO_ALERT_STATE;
			}
		}
	}
}

int From_UnlockState()
{
	// Initialize variables and LCD monitor
	tone(BUZZER_Pin, GOOD_FREQ, 400);
	unlockSolenoid();
	lcd.clear();
	lcd.print("Unlocked");
	// Wait until Exit key is pressed
	while(key != '*') {
		key = keypad.getKey();
		delay(50);
	}
	return TO_IDLE_STATE;
}

int From_AlertState()
{
	// Initialize variables and LCD monitor
	lcd.display();
	lcd.clear();
	lcd.print("Access Denied");
	tone(BUZZER_Pin, BAD_FREQ);
	validRFID_Read = false;
	if (motion_detected == HIGH) {
		lcd.setCursor(0, 1);
		lcd.print("INTRUDER");
	}
	// Wait until valid RFID is detected
	while (validRFID_Read == false) {
		validRFID_Read = validRFID();
		delay(50);
	}
	// Go to admin mode
	return TO_ADMIN_STATE;
}

int From_AdminState()
{
	// Initialize variables and LCD monitor
	noTone(BUZZER_Pin);
	motion_detected = false;
	unlockSolenoid();
	lcd.clear();
	lcd.print("ADMIN: options");
	lcd.setCursor(0, 1);
	lcd.print("-A -B -C '*'");
	key = NO_KEY;
	// Wait in a loop until user presses a key
	while(key != '*') {
		key = keypad.getKey();
		delay(50);
	}
	return TO_IDLE_STATE;
}
