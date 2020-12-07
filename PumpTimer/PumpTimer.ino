
const int voltagePin =  4;
const int pumpPin =  5;
const int switchTime =  6*60*60;

int pumpState = 0;
int timerCounter = 0;

void setup() {
  pinMode(voltagePin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(voltagePin, HIGH);
  digitalWrite(pumpPin, LOW);
  pumpState = 0;
  timerCounter = 0;
}

void loop() {
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
