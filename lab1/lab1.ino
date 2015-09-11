
const int inPins[] = {A0, 8};
const int outPins[] = {9, 10, 11, 12, 13};

int prevState = LOW;
int state = LOW;
int pressCount = 0;
float ratio = 1.0;
long currTime = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  for (int i = 0; i < sizeof(inPins); i++) {
    pinMode(inPins[i], INPUT);
  }
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
  int wait = 50 * ratio;  // in milliseconds
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
  int wait = 100 * ratio;
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
  int wait = 100 * ratio;
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
  int wait = 100 * ratio;
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
  state = digitalRead(inPins[1]);

  if (state != prevState) {
    if (state == HIGH) {
      pressCount++;
    }
  }

  prevState = state;
}

void cycle() {

  checkButton();

  // Serial.println(pressCount);

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
  currTime = millis();
  int val = analogRead(inPins[0]);
  float voltage= val * (5.0 / 1023.0);
  ratio = 5.0 / (3.6 * voltage - 0.8);
  ratio = ((int)((ratio + 0.25) / 0.5)) * 0.5;
  ratio = min(max(ratio, 0.5), 2.5);
  cycle();
}
