/**
 * Niffty Discription of what the project does 
 *  - Andrew Brady
 */

 
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 13, d0 = 11, d1 = 10, d2 = 9, d3 = 8, d4 = 7, d5=6, d6=5, d7 = 4;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3, d4, d5, d6, d7);

// D3 is SW8
// D2 is SW7
// D18 is SW6
// D19 is SW5
// D20 is SW4
// D21 is SW3
// D22 is SW2
// D23 is SW1
const int sw1 = 23, sw2 = 22, sw3 = 21, sw4 = 20, sw5 = 19, sw6 = 18, sw7 = 2, sw8 = 3;
const int swPins[] = {
  sw1, sw2, sw3, sw4, sw5, sw6, sw7, sw8
};

// D15 E
const int eButton = 15;

// D14 Resgister Select Button
const int resButton = 14;

// D16 - Program Button
const int progButton = 16;
// D17 - M1 Memory Slot?
const int m1 = 17;

int curColPos = 0;
int curRowPos = 0;

void setup() {
  for (int thisPin = 0; thisPin <7; thisPin++){
    pinMode(thisPin, INPUT);
  }
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.blink();
}

void loop() {

  int eButtonState = digitalRead(eButton);
  int resButtonState = digitalRead(resButton);

  // Read all our switches state
  byte swState[8];
  for (int thisPin = 0; thisPin <8; thisPin++){
    swState[thisPin] = digitalRead(swPins[thisPin]);
  }

  lcd.setCursor(curColPos,curRowPos);

  // Here is where we might do a command for BOTH buttons, such as sending
  //  a command (turn off the blinker)
  
  if(eButtonState == 1){
    byte b = 0;
    for( int i = 0; i < 8; i++){
      b += (swState[i] << (7-i));
    }
    lcd.write(b);
  }

  if(resButtonState == 1){
    curColPos++;
  }

  if(digitalRead(progButton) == 1 and digitalRead(m1) == 1){
    curColPos--;
    if (curColPos < 0){
      curColPos = 0;
    }
  } else {

    if(digitalRead(progButton) == 1){
      lcd.cursor();
    }
  
    if(digitalRead(m1) == 1){
      lcd.noCursor();
    }
    
  }
  
  delay(250);
}
