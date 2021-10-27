#include <SoftwareSerial.h>
void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(String(random(12,45)));
    delay(1000);
}
