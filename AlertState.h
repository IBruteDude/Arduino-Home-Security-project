#include "StateFunctions.h"

int AlertSTATE(){  // Check if the entered password is correct, then unlock the door

	if (password == CORRECT_PASS) {  // unlock the solenoid lock
      unlockDoor();  				

      lcd.setCursor(0, 1);
      lcd.print("Door unlocked!");
      delay(3000);
      lcd.clear();
      lcd.print("Enter Password:");
      password = 0;
    }
    
    if (digitalRead(pirPin) == HIGH) {  // If PIR sensor detects motion, set door to locked state and sound alarm
      doorLocked = true;
      lcd.setCursor(0, 1);
      lcd.print("Intruder detected!"); 
      digitalWrite(buzzerPin, HIGH);
      delay(5000);
      lcd.clear();
      lcd.print("Enter Password:");
      digitalWrite(buzzerPin, LOW);
    }
    else { // If no motion detected, lock the door
    lockDoor();
    lcd.setCursor(0, 1);
    lcd.print("Door locked!");
    delay(3000);
    lcd.clear();
    lcd.print("Enter Password:");
    enteredPassword = 0;
  }
}

int From_AlertState()
{
	tone(buzzerPin, FREQ);
	lcd.clear();
	lcd.print("Access Denied");
	if (motion_detected == true) {
		lcd.setCursor(0, 1);
		lcd.print("INTRUDER");
	}

	// Check for RFID reader, and when true return TO_ADMIN
}