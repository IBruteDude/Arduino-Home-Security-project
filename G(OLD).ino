#include <Keypad.h>
#include <LiquidCrystal.h>

// Define the pin numbers for the IR sensor, the buzzer, and the lock
#define IRpin 12
#define buzzerPin 13
#define lockpin 14

// Define the durations for the alarm and the retry interval
#define alarmDuration 1000
#define retryDuration 3000

// Define the keypad layout
#define ROWS 4
#define COLS 4
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the LCD pins and dimensions
LiquidCrystal lcd(2, 3, 14, 15, 16, 17);

// Define the correct password and password length
#define CORRECT_PASS "1234"
#define PASS_LEN 4

// Define variables to keep track of password attempts and PIR sensor state
String v_passcode = "";
int wrongAttempts = 0;
int pirState = 0;
char key = NO_KEY;

void setup()
{
    // Initialize the LCD and print the startup message
    lcd.begin(16, 2);
    lcd.print("Bismillah");

    // Set the pin modes for the IR sensor, buzzer, and lock
    pinMode(IRpin, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);
    pinMode(lockpin, OUTPUT);
}

void loop()
{
    // Read the IR sensor value
    int readValue = digitalRead(IRpin);
    
    // Prompt the user to enter the password and read the input from the keypad
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    while (v_passcode.length() < PASS_LEN) {
        // Reset the key variable to indicate no key pressed
        key = NO_KEY;

        // Wait for a key press
        while (key == NO_KEY) {
            key = keypad.getKey();
            
            // If the PIR sensor is triggered, clear the entered password
            if (readValue == HIGH) {
                v_passcode = "";
                break;
            }
        }

        // If a key is pressed, add it to the entered password and show an asterisk on the LCD
        if (key != NO_KEY) {
            v_passcode += key;
            lcd.setCursor(v_passcode.length(), 1);
            lcd.print("*");
        }
    }

    // If the entered password has the correct length, clear the LCD and check if it is correct
    if (v_passcode.length() == PASS_LEN) {
        lcd.clear();
        if (v_passcode == CORRECT_PASS) {
            // If the password is correct, open the lock and reset the wrongAttempts counter
            lcd.print("YOU CAN PASS");
            digitalWrite(lockpin, HIGH);
            delay(5000);
            digitalWrite(lockpin, LOW);
            wrongAttempts = 0;
        } else {
            // If the password is incorrect, increment the wrongAttempts counter and show a
        v_passcode = "";
        }
        // If the PIR sensor detects motion or the entered password is incorrect
    if (readValue == LOW || v_passcode != CORRECT_PASS) {
        // Display "INTRUDER" on the LCD screen
        lcd.clear();
        lcd.print("INTRUDER");
        // Sound the buzzer
        tone(buzzerPin, 400);
        delay(100);
        noTone(buzzerPin);
    }
    
    // Wait for the retry duration before clearing the LCD and password
    delay(retryDuration);
    lcd.clear();
    v_passcode = "";
 }
}

 // IEMTIYAZ && GHADA  