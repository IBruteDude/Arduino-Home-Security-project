#ifndef STATE_FUNCTIONS_H
#define STATE_FUNCTIONS_H
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SPI.h>

#include "IdleState.h"
#include "InputState.h"
#include "UnlockState.h"
#include "AlertState.h"
#include "AdminState.h"


#define pirPin 12
#define buzzerPin 13
#define FREQ 400
#define alarmDuration 1000
#define retryDuration 3000
#define ROWS 4
#define COLS 4
#define CORRECT_PASS "1234"
#define PASS_LEN 4
#define idleDuration 300890


inline char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
inline byte rowPins[ROWS] = {4, 5, 6, 7};
inline byte colPins[COLS] = {8, 9, 10, 11};
  
inline Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

inline LiquidCrystal lcd(2, 3, 14, 15, 16, 17);

inline bool pirState, lockState, adminApproved, inputState, lcdState;
inline String v_passcode = "";
inline int wrongAttempts = 0;
inline unsigned long upTime;
inline unsigned long startingTime;
inline char key = NO_KEY;
#endif
