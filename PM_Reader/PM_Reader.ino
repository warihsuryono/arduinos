#include <SoftwareSerial.h>
SoftwareSerial serial(3,2);
String read_string = "";
void setup() {
  Serial.begin(9600);
  serial.begin(9600);
}

void loop() {
    read_string="";
    
    serial.print(Serial.read());
    delay(100);
    if(serial.available() > 0){
      while(serial.available() > 0){
        char c = serial.read();
        read_string = read_string + c;
        delay(1);
      }
      Serial.println(read_string);
    }
}
