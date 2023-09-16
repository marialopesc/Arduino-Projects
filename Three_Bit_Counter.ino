
/*
Maria Bezerra, UIN: 676493398, netID: mbeze2
Lab 2 - Three Bit Counter


- Description - what is this code supposed to do? 
 It reads from two buttons connected to digital pins 11 and 13. When the button on pin 11 is pressed, a 
 counter (pressCount) is incremented, and when the button on pin 13 is pressed, the counter is decremented. 
 However, the code contains a mistake: the function binary(int value) doesn't properly update the LEDs according 
 to the pressCount, as it only returns whether the bitwise AND between pressCount and value is nonzero, 
 but doesn't actually change the state of the LEDs accordingly.

- Include any assumptions you may have made, what do you expect from the hardware,
pinouts, particular arduino versions, etc
    It assumes that the LEDs have current-limiting resistors, relies on the millis() function for timing, 
and sequentially lights up the LEDs with a chasing light effect, one at a time, using a 1000-millisecond 
interval between transitions.


- References - where did you find code snippets, ideas, inspirations? 
    I used the links provided and talked to TA's (ELijah) to learn more on how arduino works. 
besides that, no other references.

- Demo to TA Elijah at 9:58am

*/


const int ledPin09 = 9;
const int ledPin07 = 7;
const int ledPin05 = 5;

const int buttonInc = 11;
const int buttonDec = 13;

int buttonStateInc = LOW;
int buttonStateDec = LOW;

int lastButtonStateInc = LOW;
int lastButtonStateDec = LOW;

unsigned long lastDebounceTimeInc = 0;
unsigned long lastDebounceTimeDec = 0;
unsigned long debounceDelay = 50;

int pressCount = 0;

void setup() {
  pinMode(ledPin09, OUTPUT);
  pinMode(ledPin07, OUTPUT);
  pinMode(ledPin05, OUTPUT);
  
  pinMode(buttonInc, INPUT_PULLUP);
  pinMode(buttonDec, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();
  
  int readingInc = digitalRead(buttonInc);
  int readingDec = digitalRead(buttonDec);
  
  // Check buttonInc for debounce
  if (readingInc != lastButtonStateInc) {
    lastDebounceTimeInc = currentMillis;
  }
  
  if (currentMillis - lastDebounceTimeInc > debounceDelay) {
    if (readingInc != buttonStateInc) {
      buttonStateInc = readingInc;
      if (buttonStateInc == LOW) {
        if (pressCount < 7) pressCount++;
      }
    }
  }
  
  // Check buttonDec for debounce
  if (readingDec != lastButtonStateDec) {
    lastDebounceTimeDec = currentMillis;
  }
  
  if (currentMillis - lastDebounceTimeDec > debounceDelay) {
    if (readingDec != buttonStateDec) {
      buttonStateDec = readingDec;
      if (buttonStateDec == LOW) {
        if (pressCount > 0) pressCount--;
      }
    }
  }
  
  // Save the last button states
  lastButtonStateInc = readingInc;
  lastButtonStateDec = readingDec;
  
  // Update LEDs based on pressCount
 digitalWrite(ledPin05, (pressCount & 1) != 0);
digitalWrite(ledPin07, (pressCount & 2) != 0);
digitalWrite(ledPin09, (pressCount & 4) != 0);
}

int binary(int value) {
  int answer = pressCount & value;
  return answer;
}
