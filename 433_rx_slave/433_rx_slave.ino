#include <Wire.h>
#include <Servo.h>
Servo servo1;
int pos = 0;

void setup() {
  servo1.attach(3);
  //Serial.begin(9600);
  Wire.begin(8);
}

void loop() {
  Wire.onReceive(receiveEvent);
  if(pos != 90){
    servo1.write(map(pos, 0, 180, 180, 0));
    //Serial.println(pos);
  }
  //delay(10);
}

void receiveEvent(int howMany) {
  pos = Wire.read();
}
