
# The Program's 5 States specification:-

 * 1. Idle state (Starting state): awaiting user action
 * 		- Active motion detection (No motion detected)
 * 		- Administration approved
 * 		- Buzzer alarm OFF
 * 		- Door locked
 * 		- LCD no display (or OFF if we can)
 * 2. Input state: receive input from Keypad or from RFID reader
 * 		- Active motion detection (No motion detected)
 * 		- Administration authorised usage
 * 		- Receiving RFID input
 * 		- Buzzer alarm OFF
 * 		- Door locked
 * 		- LCD prompts for user input
 * 		- Check for correct pass input or prompt for 2 more retrials
 * 3. Alert state: the PIR signaled a motion detection
 * 		- Active motion detection (motion detected)
 * 		- Administration unauthorised usage
 * 		- Receiving RFID input
 * 		- Buzzer alarm ON
 *		- Door locked
 * 		- LCD displays an Intruder warning message
 * 4. Unlock state: the door is unlocked
 * 		- Disabled motion detection
 * 		- Administration unauthorised usage
 * 		- Ignore RFID input
 * 		- Buzzer alarm OFF
 * 		- Door Unlocked
 * 		- LCD displays an Unlocked user message
 * 5. Admin state:
 * 		- Disabled motion detection
 * 		- Administration authorised usage
 * 		- Ignore RFID input
 * 		- Buzzer alarm OFF
 * 		- Door Unlocked
 * 		- LCD prompts for #admin options#

# The Program's State transitions:-

 Idle state --['#' (Start) button is pressed]--> Input state
 Input state --[correct password input]--> Unlock state
 Unlock state --['*' (Exit) button is pressed]--> Idle state

 Input state --[incorrect password for 3 times (or motion detected)]--> Alert state
 Alert state --[valid admin RFID scanned]--> Admin state
 Admin state --['*' (Exit) button is pressed]--> Idle state

 Input state --[Idle duration is exceeded with no input]--> Idle state
 Input state --[correct RFID signal received]--> Admin state
 
