// #include <Key.h>
// #include <Keypad.h>
// #include <LiquidCrystal.h>
// #include <SPI.h>

// #define pirPin 12
// #define buzzerPin 13
// #define FREQ 400
// #define alarmDuration 1000
// #define retryDuration 3000
// #define ROWS 4
// #define COLS 4
// #define CORRECT_PASS "1234"
// #define PASS_LEN 4
// #define idleDuration 300890

// char keys[ROWS][COLS] = {
// 	{'1', '2', '3', 'A'},
// 	{'4', '5', '6', 'B'},
// 	{'7', '8', '9', 'C'},
// 	{'*', '0', '#', 'D'}
// };
// byte rowPins[ROWS] = {4, 5, 6, 7};
// byte colPins[COLS] = {8, 9, 10, 11};
// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LiquidCrystal lcd(2, 3, 14, 15, 16, 17);

// bool pirState;
// bool lockState;
// bool adminApproved;
// bool inputState;
// bool lcdState;
// String v_passcode;
// int wrongAttempts;
// unsigned long upTime;
// unsigned long startingTime;
// char key;

// void setup() {
// 	lcd.begin(16, 2);
// 	lcd.print("Bismillah");
// 	lcd.blink();
// 	lcd.noDisplay();
// 	lcdState = false;

// 	pinMode(pirPin, INPUT);
// 	pinMode(buzzerPin, OUTPUT);

// 	pirState = lockState = false;
// 	inputState = adminApproved = true;
// 	v_passcode = "";
// 	wrongAttempts = 0;
// 	key = NO_KEY;
// 	startingTime = millis();
// }

// void loop() {
// 	// Initialise LCD for recieving input
// 	lcd.setCursor(0, 0);
// 	lcd.print("Enter Password:");

// 	// Check for command to turn LCD monitor ON
// 	if (lcdState == false && keypad.getKey() == '#') {
// 		lcd.display();
// 		lcdState = true;
// 		inputState = true;
// 	}

// 	// Check if LCD idleDuration is exceeded to turn it off
// 	upTime = millis() - startingTime;
// 	if (lcdState == true && upTime == idleDuration) {
// 		lcd.noDisplay();
// 		lcdState = false;
// 		inputState = false;
// 	}
	
// 	// pirState = digitalRead(pirPin);

// 	/** 
// 	 * Receiving input from the KeyPad and storing it
// 	 * - Reading from the RFID for admin access
// 	 * - Also monitors the PIR motion detection
// 	 */
// 	while (inputState && v_passcode.length() < PASS_LEN) {
// 		key = NO_KEY;
// 		// The main input reading loop
// 		while (key == NO_KEY) {
// 			key = keypad.getKey();
// 			// pirState = digitalRead(pirPin);
// 			if (pirState == HIGH && lockState == false)
// 				break;
// 		}
// 		if (pirState == HIGH && lockState == false)
// 			break;
// 		v_passcode += key;
// 		lcd.setCursor(v_passcode.length(), 1);
// 		lcd.print('*');
// 	}
// 	/**
// 	 * 	In case of successfully receiving Input:
// 	 * 	- Check for password input
// 	 */
// 	if (v_passcode.length() == PASS_LEN) {
// 		lcd.clear();
// 		if (v_passcode == CORRECT_PASS) {
// 			lcd.print("Correct Pass");
// 			wrongAttempts = 0;
// 			// Unlock the solenoid lock
// 			lockState = true;
// 		} else {
// 			lcd.print("Incorrect Pass");
// 			wrongAttempts++;
// 			if (wrongAttempts >= 3) {
// 				// Set to alert state and require Administration approval
// 				tone(buzzerPin, FREQ, alarmDuration);
// 				wrongAttempts = 0;
// 				adminApproved = false;
// 			} else {
// 				// Set LCD to retrial state
// 				lcd.setCursor(0, 1);
// 				lcd.print(3 - wrongAttempts);
// 				lcd.setCursor(1, 1);
// 				lcd.print(" attempts left");
// 				delay(retryDuration);
// 				lcd.clear();
// 				v_passcode = "";
// 			}
// 		}
// 	}
// 	/**
// 	 * If PIR detects motion from an intruder
// 	 * Sound the alarm
// 	 */
// 	if (pirState == HIGH && lockState == false) {
// 		lcd.clear();
// 		lcd.print("INTRUDER!");
// 		tone(buzzerPin, FREQ);
// 	}
// }