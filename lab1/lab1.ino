/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

const int inPin = 8;
const int outPins[] = {9, 10, 11, 12, 13};

int prevState = LOW;
int state = LOW;
int pressCount = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(inPin, INPUT);
  for (int i = 0; i < sizeof(outPins); i++) {
    pinMode(outPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void allOn() {
  for (int thisPin = 9; thisPin <= 13; thisPin++) {
    digitalWrite(thisPin, HIGH);
  }
}

void allOff() {
  for (int thisPin = 9; thisPin <= 13; thisPin++) {
    digitalWrite(thisPin, LOW);
  }
}

void bounce() {
  allOff();
  for (int thisPin = 9; thisPin <= 12; thisPin++) {
    digitalWrite(thisPin, HIGH);
    checkButton();
    delay(50);
    digitalWrite(thisPin, LOW);
  }
  for (int thisPin = 13; thisPin >= 10; thisPin--) {
    digitalWrite(thisPin, HIGH);
    checkButton();
    delay(50);
    digitalWrite(thisPin, LOW);
  }
}

void allBlink() {
  allOff();
  for (int thisPin = 9; thisPin <= 13; thisPin++) {
    digitalWrite(thisPin, HIGH);
    checkButton();
    delay(100);
    digitalWrite(thisPin, LOW);
  }
}

void allFlash() {
  allOn();
  checkButton();
  delay(100);
  allOff();
  checkButton();
  delay(100);
}

void checkButton() {
  state = digitalRead(8);

  if (state != prevState) {
    if (state == HIGH) {
      pressCount++;
    }
  }

  prevState = state;
}

void cycle() {

  checkButton();
  
  if (pressCount % 5 == 0) {
    allOn();
  }
  if (pressCount % 5 == 1) {
    allOff();
  }
  if (pressCount % 5 == 2) {
    allBlink();
  }
  if (pressCount % 5 == 3) {
    bounce();
  }
  if (pressCount % 5 == 4) {
    allFlash();
  }
}

//// the loop function runs over and over again forever
void loop() {
  cycle();
}
