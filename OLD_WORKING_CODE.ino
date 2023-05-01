#include <Keypad.h>
#include <LiquidCrystal.h>

#define pirPin 12
#define buzzerPin 13
#define alarmDuration 1000
#define retryDuration 3000
#define ROWS 4
#define COLS 4
#define CORRECT_PASS "1234"
#define PASS_LEN 4

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(2, 3, 14, 15, 16, 17);

String v_passcode = "";
int wrongAttempts = 0;
int pirState = 0;
char key = NO_KEY;

void setup()
{
	lcd.begin(16, 2);
	lcd.print("Bismillah");
	pinMode(pirPin, INPUT_PULLUP);
	pinMode(buzzerPin, OUTPUT);
}
void loop()
{
	lcd.setCursor(0, 0);
	lcd.print("Enter Password:");
	while (v_passcode.length() < PASS_LEN) {
		key = NO_KEY;
  		while (key == NO_KEY) {
			key = keypad.getKey();
			// pirState = digitalRead(pirPin);
			if (pirState == HIGH)
				break;
    		}
	    	v_passcode += key;
		lcd.setCursor(v_passcode.length(), 1);
        	lcd.print("*");
        	if (pirState == HIGH)
        		break;
	}
	if (v_passcode.length() == PASS_LEN) {
		lcd.clear();
		if (v_passcode == CORRECT_PASS) {
			lcd.print("YA FARAG ALLAH");
			wrongAttempts = 0;
		} else {
			lcd.print("Incorrect Pass");
        		wrongAttempts++;
			if (wrongAttempts >= 3) {
        			tone(buzzerPin, 400, 1000);
				wrongAttempts = 0;
			} else {
        			lcd.setCursor(0, 1);
        			lcd.print(3 - wrongAttempts);
        			lcd.setCursor(1, 1);
            			lcd.print(" attempts left");
			}
		}
	}
	if (pirState == HIGH && v_passcode != CORRECT_PASS) {
		lcd.clear();
		lcd.print("INTRUDER");
		tone(buzzerPin, 400);
		delay(100);
		noTone(buzzerPin);
	}
	delay(retryDuration);
	lcd.clear();
	v_passcode = "";
}