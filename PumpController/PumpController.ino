#include <SoftwareSerial.h>
int pump1 = 12;
int pump2 = 11;
char inChar;
void setup() {
    Serial.begin(9600);
    pinMode(pump1, OUTPUT);
    pinMode(pump2, OUTPUT);
    digitalWrite(pump1,HIGH);
    digitalWrite(pump2,LOW);
}

void loop() {
    if (Serial.available() > 0) {
        inChar = Serial.read();
        if(inChar == 'i'){
            digitalWrite(pump1,HIGH);
            digitalWrite(pump2,LOW);
        }
        if(inChar == 'j'){
            digitalWrite(pump1,LOW);
            digitalWrite(pump2,HIGH);
        }
    }
}
