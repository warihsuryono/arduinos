#include <SoftwareSerial.h>
int ain0 = 3;
int ain1 = 5;
int ain2 = 6;
int ain3 = 9;
int ain4 = 10;
void setup() {
    Serial.begin(9600);
    pinMode(ain0, OUTPUT);
    pinMode(ain1, OUTPUT);
    pinMode(ain2, OUTPUT);
    pinMode(ain3, OUTPUT);
    pinMode(ain4, OUTPUT);
}

void loop() {
    Serial.println("000.0" + String(random(10,12)) + "," + String(float(random(20,22))/10).substring(0,3) +",+28.3,067,1007.4,00,*01543,");
    delay(1000);

    analogWrite(ain0,2);
    analogWrite(ain1,2);
    analogWrite(ain2,2);
    analogWrite(ain3,2);
    analogWrite(ain4,2);
}
