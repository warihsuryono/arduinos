
const int buttonPin = 3;
const int voltagePin =  4;
const int pumpPin =  5;
const int switchTime =  6*60*60;

int buttonState = 0;
int pumpState = 0;
int timerCounter = 0;

void setup() {
  pinMode(voltagePin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(voltagePin, LOW);
  digitalWrite(pumpPin, LOW);
  pumpState = 0;
  timerCounter = 0;
}

void loop() {
  buttonState = digitalRead(buttonPin);
  //if (buttonState == LOW) { switchPump(); }
  if(timerCounter >= switchTime){ switchPump(); }
  timerCounter++;
  delay(1000);
}

void switchPump(){
  if (pumpState == 0) {
    pumpState = 1;
    digitalWrite(pumpPin, HIGH);
  }else{
    pumpState = 0;
    digitalWrite(pumpPin, LOW);
  }
  timerCounter = 0;
}
