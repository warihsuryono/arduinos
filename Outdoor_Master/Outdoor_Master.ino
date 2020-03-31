#include <SoftwareSerial.h>

SoftwareSerial text1(2,3);
String read_string = "";

void setup() {
    Serial.begin(9600);
    text1.begin(1200);
}

void loop() {
    if(Serial.available() > 0){
        read_string = Serial.readString();
        text1.print(read_string);
    }
}
