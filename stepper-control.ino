#include <EEPROM.h>

// Four pins on stepper motor
int p1 = 2;
int p2 = 3;
int p3 = 4;
int p4 = 5;

// Pin from power source
int powerPin = 6;

// Data tracking pins
int i = 0;
int c = 0;
int bound = 230;
int a = 0;
int aDir = 9;
int dir = 1;
int prevPower = 0;

void setup() {
  Serial.begin(9600);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(powerPin, INPUT);
  clearPins();

  c = EEPROM.read(a);
//  dir = EEPROM.read(aDir);
  Serial.println("LOADED c and dir from EEPROM");
}

void loop() {
  if(digitalRead(powerPin)) {
    if( (c < bound) && dir == 1) {
      forwards();
      Serial.println(c);
    }
    else if((c == bound) && dir == 1) {
      // Reset location data when changing directions
      i = 0;
      c = 0;
      dir = 0;
    }
    else if((c == bound) && dir == 0) {
      i = 0;
      c = 0;
      dir = 1;
    }
    else if ((c < bound) && dir == 0){
      backwards();
      Serial.println(c);
    }
  }
  else if(prevPower == 1) {
    // If power was just turned off, save location of stepper motor to EEPROM
    EEPROM.write(a, c);
    EEPROM.write(aDir, dir);
    Serial.println("SAVED c to EEPROM");
  }
  // Save state of previous power to motor
  prevPower = digitalRead(powerPin);

  delay(1);
   clearPins();
}

/**
 * Apply power to four pins on stepper motor in four steps.
 * Everytime this function is called, stepper motor
 * goes forward one step (tick). Therefore you may put this function
 * in a loop and modify delay to change the speed. Variable c
 * stores location of the stepper motor relative to its last boundary
 */
void forwards() {
  if(i == 0) {
       digitalWrite(p1, HIGH);
       digitalWrite(p2, LOW);
      }
      else if(i == 1) {
        digitalWrite(p3, HIGH);
        digitalWrite(p4, LOW);
      }
      else if(i == 2) {
        digitalWrite(p1, LOW);
        digitalWrite(p2, HIGH);
      }
      else if(i == 3) {
        digitalWrite(p3, LOW);
        digitalWrite(p4, HIGH);
      }
      if(i == 3) {
        i = 0;
      }
      else {
        i++;
      }
      c++;
}

/**
 * Same function as forwards, with ticks in reverse.
 * Since stepper motor direction is symmetrical we can power
 * pins in reverse to the forwards function
 */
void backwards() {
      if(i == 0) {
        digitalWrite(p3, LOW);
        digitalWrite(p4, HIGH);
      }
      else if(i == 1) {
        digitalWrite(p1, LOW);
        digitalWrite(p2, HIGH);
      }
      else if(i == 2) {
         digitalWrite(p3, HIGH);
         digitalWrite(p4, LOW);
      }
      else if(i == 3) {
        digitalWrite(p1, HIGH);
         digitalWrite(p2, LOW);
      }
      if(i == 3) {
        i = 0;
      }
      else {
        i++;
      }
      c++;
}

// Reset stepper motor pins
void clearPins() {
  digitalWrite(p1, HIGH);
   digitalWrite(p3, HIGH);
   digitalWrite(p2, HIGH);
   digitalWrite(p4, HIGH);
}

// Wrapper for digitalWrite to write HIGH on pin if out is 1, LOW if out is 0
void write(int pin, int out) {
  if(out == 1) {
    digitalWrite(pin, LOW);
  }
  else {
    digitalWrite(pin, HIGH);
  }
}

