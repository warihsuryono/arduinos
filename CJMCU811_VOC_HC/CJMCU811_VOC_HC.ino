#include <SoftwareSerial.h>
#include "Adafruit_CCS811.h"
Adafruit_CCS811 ccs;
SoftwareSerial com(4,5);
void setup() {
  //Serial.begin(9600);
  com.begin(4800);
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
}
void loop() {
  if(ccs.available()){
    float temp = ccs.calculateTemperature();
    if(!ccs.readData()){
      com.println(ccs.getTVOC());
      //Serial.println(ccs.getTVOC());
    }else{
      //Serial.println("ERROR!");
      while(1);
    }
  }
  delay(1000);
}
