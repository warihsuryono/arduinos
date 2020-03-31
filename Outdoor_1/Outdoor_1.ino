#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial_bold_14.h>
const int WIDTH = 1;
char *curr_message = "PT. TRUSUR          ";
char *show_message; 
char read_char[200];
String read_string = "";
bool reading;

SoftDMD dmd(WIDTH,1);
DMD_TextBox box(dmd,0,1,32,0);//L,T,W,H

void setup() {
    Serial.begin(9600);
    dmd.setBrightness(255);
    dmd.selectFont(Arial14);
    dmd.begin();
}

void loop() {
    if(Serial.available() > 0){
        reading = true;
        read_string = Serial.readString();
        read_string.trim();
        read_string = "| " + read_string + "          |";
        Serial.println(read_string);
        for (int i = 0; i <= read_string.length(); i++) {
            read_char[i] = read_string[i];
        }
        curr_message = read_char;
        reading = false;
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
