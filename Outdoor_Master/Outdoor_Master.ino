#include <SoftwareSerial.h>

SoftwareSerial text1(2,3);
SoftwareSerial text2(5,6);
SoftwareSerial text3(10,11);

String read_string = "";
String data = "";
int str_length = 0;

void setup() {
    Serial.begin(9600);
    text1.begin(110);
    text2.begin(110);
    text3.begin(110);
}

void loop() {
    if(Serial.available() > 0){
        read_string = Serial.readString();
        str_length = read_string.length();
        data = read_string.substring(1,str_length-1);
        if(String(read_string[0]) == "1"){
            text1.print(data);
            Serial.println("OK");
        } else if(String(read_string[0]) == "2"){
            text2.print(data);
            Serial.println("OK");
        } else if(String(read_string[0]) == "3"){
            text3.print(data);
            Serial.println("OK");
        } else {
            Serial.println("Error");
        }
    }
}
