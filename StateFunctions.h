#ifndef STATE_FUNCTIONS_H
#define STATE_FUNCTIONS_H
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SPI.h>


#define pirPin 12
#define buzzerPin 13
#define FREQ 400
#define alarmDuration 1000
#define ROWS 4
#define COLS 4

#define TO_IDLE_STATE 0
#define TO_INPUT_STATE 1
#define TO_UNLOCK_STATE 2
#define TO_ALERT_STATE 3
#define TO_ADMIN_STATE 4


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

int From_IdleState();
int From_InputState();
int From_UnlockState();
int From_AlertState();
int From_AdminState();

inline bool motion_detected, lockState, inputState, lcdState;
inline char pressedKey = NO_KEY;
inline String CORRECT_PASS = "1234";
#endif
