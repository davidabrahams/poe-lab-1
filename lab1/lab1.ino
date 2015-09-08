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


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
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
    delay(50);
    digitalWrite(thisPin, LOW);
  }
  for (int thisPin = 13; thisPin >= 10; thisPin--) {
    digitalWrite(thisPin, HIGH);
    delay(50);
    digitalWrite(thisPin, LOW);
  }
}

void allBlink() {
  allOff();
  for (int thisPin = 9; thisPin <= 13; thisPin++) {
    digitalWrite(thisPin, HIGH);
    delay(1000);
    digitalWrite(thisPin, LOW);
    delay(1000);
  }
}

void allFlash() {
  allOn();
  delay(1000);
  allOff();
  delay(1000);
}

//// the loop function runs over and over again forever
void loop() {
  bounce();
}
