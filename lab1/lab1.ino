
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
  for (int i = 0; i < sizeof(outPins); i++) {
    digitalWrite(outPins[i], HIGH);
  }
}

void allOff() {
  for (int i = 0; i < sizeof(outPins); i++) {
    digitalWrite(outPins[i], LOW);
  }
}

void allOffExcept(int pin)
{
  for (int i = 0; i < sizeof(outPins); i++) {

    // If the currnet output pin is in the input, then turn this pin on.
    if (pin == outPins[i]) {
      digitalWrite(outPins[i], HIGH);
    } else {
      digitalWrite(outPins[i], LOW);
    }
  }
}

void allOffExcept(int pin1, int pin2)
{
  for (int i = 0; i < sizeof(outPins); i++) {

    // If the currnet output pin is in the input, then turn this pin on.
    if (pin1 == outPins[i] || pin2 == outPins[i]) {
      digitalWrite(outPins[i], HIGH);
    } else {
      digitalWrite(outPins[i], LOW);
    }
  }
}

void bounce() {


  int phases = 8;
  int wait = 50;  // in milliseconds
  int currentPhase = (currTime % (wait * phases)) / wait;
  
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

void wheel() {

  int phases = 5;
  int wait = 100;
  int currentPhase = (currTime % (wait * phases)) / wait;

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

void zigzag()
{
  int phases = 4;
  int wait = 100;
  int currentPhase = (currTime % (wait * phases)) / wait;

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

void allFlash() {
  
  int phases = 2;
  int wait = 100;
  int currentPhase = (currTime % (wait * phases)) / wait;

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

void checkButton() {
  state = digitalRead(inPin);

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
    bounce();
  }
  if (pressCount % 5 == 3) {
    zigzag();
  }
  if (pressCount % 5 == 4) {
    allFlash();
  }
}

//// the loop function runs over and over again forever
void loop() {
//  checkButton();
  currTime = millis();
  cycle();
//allFlash();
//  allOffExcept(outPins[4]);
}
