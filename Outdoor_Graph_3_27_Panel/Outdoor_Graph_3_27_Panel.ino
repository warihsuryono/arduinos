#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
SoftwareSerial master(4,5);
SoftwareSerial slave(2,3);
const int bar_width = 16;
const int WIDTH = 3; 
char read_char[200];
String read_string = "";
bool reading;
String no2_s;
int no2;
int i = 0;

int no2_x = 0;
int no2_y = 0;

SoftDMD dmd(WIDTH,1);

void setup() {
    Serial.begin(9600);
    slave.begin(110);
    master.begin(110);
    dmd.setBrightness(255);
    dmd.begin();
    Serial.println("Begin");
}

void loop() {
    if(master.available() > 0){
        read_string = master.readString();
        Serial.print(read_string);
        delay(200);
        if(String(read_string[0]) == "2"){
            int i_var = 0;
            no2_s = "";
    
            for (int x = 0; x <= read_string.length(); x++) {
                if(String(read_string[x]) == ";" || String(read_string[x]) == "]") {
                    if(String(read_string[x]) == "]") x = 200;
                    i_var++;
                }else {
                    if(i_var == 5) no2_s += String(read_string[x]);
                }
            }
            dmd.clearScreen();
            Serial.println("OK");
        } else {
            slave.println(read_string);
        }
    }
    
    no2 = no2_s.toInt();
    Serial.println(no2_s);

    no2 = map(no2_s.toInt(), 0, 500, 0, 95);
    dmd.drawFilledBox(no2_x,no2_y,(no2 + no2_x),(bar_width - 1));
    delay(100);
}
