#include <SoftwareSerial.h>
void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(String(random(1,12)) + "." + String(random(1,12)));
    delay(1000);
}
