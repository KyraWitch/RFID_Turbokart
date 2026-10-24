//To do!

//----Bluetooth----
// Add serial output for RFID card read
// Add serial input for bool if card is authorized or not

//----RFID----
// Read up on RFID
// Add RFID reader to project
// Add RFID card read to serial output

//----Serial ints----

//----Pin mapping----
//RFID reader pins
//Bluetooth pins
//LCD pins

//Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <rfid1.h>

//-------------- Pin Assignment ----------------
  //Colour pins
  const int Greenpin = 2;
  const int yellowpin = 3;
  const int Redpin = 4;

  //Buzzer Pins
  const int sigB = 2; // Signal Buzzer


  //------ LCD -------
  LiquidCrystal_I2C lcd(0x27, 16, 2);

  //----- Buzzer scheduler ------
  bool buzzOn = false;
  uint32_t BuzzNext = 0; // When Buzzer next can buzz
  uint16_t buzzOnMs = 20; // Change Buzzer on ms
  uint16_t buzzOffMs = 200; // Change buzzer off ms

  // LED State
void setIdleIndicators() { //Idle
	digitalWrite(greenPin, HIGH);
	digitalWrite(redPin, LOW);
}

void setAlertIndicators() { //DANGER
	digitalWrite(redPin, HIGH);
	digitalWrite(greenPin, LOW);
}


// LCD messages
void lcdSetEmpty() {
	lcd.clear();
	lcd.setCursor(1, 0);
	lcd.print("Authorized, Welcome.");
	lcd.setCursor(0, 1);
	lcd.print("          ");
}

void lcdSetWarning() {
	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print ("Unregionized Access");
	lcd.setCursor(2, 1);
	lcd.print("Please try again.");
}

// Update LCD If stage changes
void updLCD(bool stage) {
	if (state != lastAlert) {
		if (state) lcdSetWarning();
		else lcdSetEmpty();
		lastAlert = state;	
	}
}



// ------ Setup -------
void setup() {
  // put your setup code here, to run once:
	
	pinMode(greenPin, OUTPUT);
	pinMode(yellowPin, OUTPUT);
	pinMode(redPin, OUTPUT);
	pinMode(sigB, OUTPUT);


	lcd.init();
	lcd.backlight();
	lcd.clear();
	lcdSetEmpty();

	setIdleIndicators();

}

void loop() {
  // put your main code here, to run repeatedly:

// Buzzer Update 
	if (alertNow) {
		if ((int32_t)(now - tBuzzNext) >= 0) {
			if (buzzOn) {
				digitalWrite(sigB, HIGH);
				buzzOn = true;
				tBuzzNext = now + buzzOnMs;
			}
			else {
				digitalWrite(sigB, LOW);
				buzzOn = false;
				tBuzzNext = now + buzzOffMs;
			}
		}
	} else {	
		digitalWrite(sigB, LOW);
		buzzOn = false;
	}

}