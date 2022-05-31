/**
 * Niffty Discription of what the project does 
 *  - Andrew Brady
 */

 
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 13, d0 = 11, d1 = 10, d2 = 9, d3 = 8, d4 = 7, d5=6, d6=5, d7 = 4;
const int dPins[] = { d0, d1, d2, d3, d4, d5, d6, d7 };
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

/**
const int swPins[] = {
  sw1, sw2, sw3, sw4, sw5, sw6, sw7, sw8
};
**/

const int swPins[] = {
  sw8, sw7, sw6, sw5, sw4, sw3, sw2, sw1
};


const int eButton    = 15; // D15 E
const int resButton  = 14; // D14 Resgister Select Button
const int progButton = 16; // D16 - Program Button
const int m1         = 17; // D17 - M1 Memory Slot?

int curColPos = 0;
int curRowPos = 0;

void print_binary(int number, byte Length){
  static int Bits;
  if (number) { //The remaining bits have a value greater than zero continue
    Bits++; // Count the number of bits so we know how many leading zeros to print first
    print_binary(number >> 1, Length); // Remove a bit and do a recursive call this function.
    if (Bits) for (byte x = (Length - Bits); x; x--) Serial.write('0'); // Add the leading zeros
    Bits = 0; // clear no need for this any more
    Serial.write((number & 1) ? '1' : '0'); // print the bits in reverse order as we depart the recursive function    
  }
}

void setup() {
  for (int thisPin = 0; thisPin <7; thisPin++){
    pinMode(swPins[thisPin], INPUT);
  }
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  lcd.setCursor(0,0);
  lcd.print("Hello World");
  delay(1000);
  lcd.clear();
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

  if(eButtonState == 1 and resButtonState == 1){
    curColPos++;  
    
  } else {
    if(eButtonState == 1){
      // Crystal Lib method
      byte b = 0;
      for( int i = 0; i < 8; i++){
        b += (swState[i] << (7-i));
      }
      //lcd.write(b);
      //Serial.println(b);
      print_binary(b, 8);
      Serial.println();
      //Duplicate above but manually
      // First RS = HIGH (for data)
      
      digitalWrite(rs, HIGH); // Next set the data pins
      for ( int i = 0; i < 8; i++){
        digitalWrite(dPins[i], swState[i]);
      }
      digitalWrite(en, HIGH);
      delay(20);
      digitalWrite(en, LOW);
      
      
      curColPos++;
      
    }
    
    if(resButtonState == 1){
      // This is for sending commands, and can assume that the en is pressed
      // First RS = LOW (for instruction)
      digitalWrite(rs, LOW);
      // Next set the data pins
      for ( int i = 0; i < 8; i++){
        digitalWrite(dPins[i], swState[i]);
      }
      digitalWrite(en, HIGH);
      delay(20);
      digitalWrite(en, LOW);

      //Now set the RS back to data
      digitalWrite(rs, HIGH);
    }
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
  
  delay(200);
}
