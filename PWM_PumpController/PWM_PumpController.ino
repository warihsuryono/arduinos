int speed;
int activePin = 0;
void setup() {
  speed = 0;
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    analogWrite(5,0);
    analogWrite(6,0);
    speed = Serial.readString().toInt();
    if(speed > 100){
      speed = map(speed,101,200,0,255);
      activePin=6;
    }else {
      speed = map(speed,0,100,0,255);
      activePin=5;
    }
  }
  analogWrite(activePin,speed);
  delay(1000);
}
