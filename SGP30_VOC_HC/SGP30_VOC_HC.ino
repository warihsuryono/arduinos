#include <SoftwareSerial.h>
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
//SoftwareSerial com(4,5);
SGP30 mySensor;
//String ccs811_string = "";
String sgp30_string = "";

void setup() {
  Serial.begin(9600);
//  com.begin(4800);
  Wire.begin();
  if (mySensor.begin() == false) {
    Serial.println("No SGP30 Detected. Check connections.");
    while (1);
  }
  mySensor.initAirQuality();
}

void loop() {
  delay(1000);
  mySensor.measureAirQuality();
//  ccs811_string = com.readString();
  sgp30_string = String(mySensor.TVOC);
  Serial.println(sgp30_string);
}
