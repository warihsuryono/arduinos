#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial_bold_14.h>
const int WIDTH = 1;
char *curr_message = "PT. TRUSUR UNGGUL TEKNUSA          ";
char *show_message; 
char read_char[200];
String read_string = "";
String text_template = "PM10: {pm10} , SO2: {so2}, CO: {co}, O3: {o3}, NO2: {no2}";
bool reading;

SoftDMD dmd(WIDTH,1);
DMD_TextBox box(dmd,0,1,32,0);//L,T,W,H

void setup() {
    Serial.begin(9600);
    dmd.setBrightness(255);
    dmd.selectFont(Arial14);
    dmd.begin();
}

String category(String val){
    if(val == "0") return "BAIK";
    else if(val == "1") return "SEDANG";
    else if(val == "2") return "TIDAK SEHAT";
    else if(val == "3") return "SANGAT TIDAK SEHAT";
    else if(val == "4") return "BERBAHAYA";
    else return "";
}

void loop() {
    if(Serial.available() > 0){
        read_string = Serial.readString();
        String pm10 = category(String(read_string[0]));
        String so2 = category(String(read_string[1]));
        String co = category(String(read_string[2]));
        String o3 = category(String(read_string[3]));
        String no2 = category(String(read_string[4]));
        read_string = " " + text_template + "          ";
        read_string.replace("{pm10}",pm10);
        read_string.replace("{so2}",so2);
        read_string.replace("{co}",co);
        read_string.replace("{o3}",o3);
        read_string.replace("{no2}",no2);
        Serial.println(read_string);
        for (int i = 0; i <= read_string.length(); i++) {
            read_char[i] = read_string[i];
        }
        curr_message = read_char;
    }
    show_message = curr_message;

    if(!reading){
        Serial.print(" ==> ");
        Serial.println(show_message);
        while(*show_message) {
            box.print(*show_message);
            delay(100);
            *show_message++;
        }
    }
}
