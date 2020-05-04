#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

void setup() {
  Serial.begin(9600);
  if(!ccs.begin()){
      Serial.println("Failed to start sensor! Please check your wiring.");
      while(1);
  }

  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
}

void loop() {
    if(ccs.available()){
        float temp = ccs.calculateTemperature();
        if(!ccs.readData()){
            String val = String(ccs.getTVOC());
            Serial.println(val);
        } else {
            while(1);
        }
    }
    delay(1000);
}
