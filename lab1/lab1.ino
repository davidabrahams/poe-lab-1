
const int inPin = 8;
const int outPins[] = {9, 10, 11, 12, 13};

int prevState = LOW;
int state = LOW;
int pressCount = 0;
long currTime = 0;

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

  phases = 8;
  speed = 50;  // in milliseconds
  currentPhase = (currTime % speed) % phases;

  switch(currentPhase)
  {

    case 0 : digitalWrite(outPins[0], HIGH);
    case 1 : digitalWrite(outPins[1], HIGH);
    case 2 : digitalWrite(outPins[2], HIGH);
    case 3 : digitalWrite(outPins[3], HIGH);
    case 4 : digitalWrite(outPins[4], HIGH);
    case 5 : digitalWrite(outPins[3], HIGH);
    case 6 : digitalWrite(outPins[2], HIGH);
    case 7 : digitalWrite(outPins[1], HIGH);

  }

}

void cycle() {

  phases = 5;
  speed = 100;
  currentPhase = (currTime % speed) % phases;

  switch(currentPhase)
  {
    case 0 : digitalWrite(outPins[0], HIGH);
    case 1 : digitalWrite(outPins[1], HIGH);
    case 2 : digitalWrite(outPins[2], HIGH);
    case 3 : digitalWrite(outPins[3], HIGH);
    case 4 : digitalWrite(outPins[4], HIGH);
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
  currTime = millis();
  cycle();
}
