
const int inPins[] = {A0, 8};  // The pins we will be reading in
const int outPins[] = {9, 10, 11, 12, 13};  // The pins we will be outputting to (The LEDs)

// Initialize all our variables
int prevState = LOW;
int state = LOW;
int pressCount = 0;
float ratio = 1.0;
long currTime = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize all the input and output pins
  for (int i = 0; i < sizeof(inPins); i++) {
    pinMode(inPins[i], INPUT);
  }
  for (int i = 0; i < sizeof(outPins); i++) {
    pinMode(outPins[i], OUTPUT);
  }
}

// Turn on all the pins
void allOn() {
  for (int i = 0; i < sizeof(outPins); i++) {
    digitalWrite(outPins[i], HIGH);
  }
}

// Turn off all the pins
void allOff() {
  for (int i = 0; i < sizeof(outPins); i++) {
    digitalWrite(outPins[i], LOW);
  }
}

// Turn off every pin except one pin, which we turn on
void allOffExcept(int pin) {
  for (int i = 0; i < sizeof(outPins); i++) {
    // If the current output pin is the argument pin, turn it on
    if (pin == outPins[i]) {
      digitalWrite(outPins[i], HIGH);
    }
    // Otherwise, turn it off
    else {
      digitalWrite(outPins[i], LOW);
    }
  }
}

// Turn off every pin except two pins, which we turn on
void allOffExcept(int pin1, int pin2) {
  for (int i = 0; i < sizeof(outPins); i++) {
    // If the current output pin is either of the argument pins, turn it on
    if (pin1 == outPins[i] || pin2 == outPins[i]) {
      digitalWrite(outPins[i], HIGH);
    }
    else {
      digitalWrite(outPins[i], LOW);
    }
  }
}

// Calculate which "phase" we're currently in. For example, if we have 4 phases, a wait time of 1000, and ratio is, then calcCurrentPhase returns 0, 1, 2, or 3, switching values every second.
int calcCurrentPhase(int phases, int wait) {
  int scaledWait = wait * ratio;
  return (currTime % (scaledWait * phases)) / scaledWait;
}

// Bounce the LED light back and forth
void bounce() {

  int currentPhase = calcCurrentPhase(8, 50);

  switch(currentPhase)
  {

    case 0 :
      allOffExcept(outPins[0]);
      break;
    case 1 :
      allOffExcept(outPins[1]);
      break;
    case 2 :
      allOffExcept(outPins[2]);
      break;
    case 3 :
      allOffExcept(outPins[3]);
      break;
    case 4 :
      allOffExcept(outPins[4]);
      break;
    case 5 :
      allOffExcept(outPins[3]);
      break;
    case 6 :
      allOffExcept(outPins[2]);
      break;
    case 7 :
      allOffExcept(outPins[1]);
      break;

  }

}

// Cycle the LED light
void wheel() {

  int currentPhase = calcCurrentPhase(5, 100);

  switch(currentPhase)
  {
    case 0 :
      allOffExcept(outPins[0]);
      break;
    case 1 :
      allOffExcept(outPins[1]);
      break;
    case 2 :
      allOffExcept(outPins[2]);
      break;
    case 3 :
      allOffExcept(outPins[3]);
      break;
    case 4 :
      allOffExcept(outPins[4]);
      break;
  }

}

// Move the LED from inside to outside
void zigzag()
{

  int currentPhase = calcCurrentPhase(4, 100);

  switch(currentPhase)
  {
    case 0 :
      allOffExcept(outPins[0], outPins[4]);
      break;
    case 1 :
      allOffExcept(outPins[1], outPins[3]);
      break;
    case 2 :
      allOffExcept(outPins[2]);
      break;
    case 3 :
      allOffExcept(outPins[1], outPins[3]);
      break;
  }
}

// Flash all LED lights
void allFlash() {

  int currentPhase = calcCurrentPhase(2, 100);

  switch(currentPhase)
  {
    case 0 :
      allOn();
      break;
    case 1 :
      allOff();
      break;
  }
}

// Read in the button pin. If It has just gone from Low To High, then register a button press.
void checkButton() {
  state = digitalRead(inPins[1]);

  if (state != prevState) {
    if (state == HIGH) {
      pressCount++;
    }
  }

  prevState = state;
}

// Based on the total number of presses, do a different LED display.
void cycle() {

  checkButton();

  if (pressCount % 6 == 0) {
    allOn();
  }
  if (pressCount % 6 == 1) {
    allOff();
  }
  if (pressCount % 6 == 2) {
    bounce();
  }
  if (pressCount % 6 == 3) {
    zigzag();
  }
  if (pressCount % 6 == 4) {
    allFlash();
  }
  if (pressCount % 6 == 5) {
    wheel();
  }
}

//// the loop function runs over and over again forever
void loop() {
  currTime = millis();  // read in the current time in milli seconds
  int val = analogRead(inPins[0]); // read in the value of the distance sensor
  float voltage= val * (5.0 / 1023.0); // convert it to a voltage from 0-5
  ratio = 5.0 / (3.6 * voltage - 0.8); // convert it to a ratio where 0.5 volts corresponds to a ratio of 5, and 3 volts corresponds to a ratio of 0.5.
  ratio = ((int)((ratio + 0.25) / 0.5)) * 0.5; // round it to the nearest 0.5 volts
  ratio = min(max(ratio, 0.5), 2.5); // coerce it inside the bounds [0.5, 2.5]
  cycle(); // display the correct LED configuration
}
