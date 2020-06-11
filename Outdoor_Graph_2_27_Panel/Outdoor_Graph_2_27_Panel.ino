#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
SoftwareSerial master(4,5);
SoftwareSerial slave(2,3);
const int bar_width = 16;
const int WIDTH = 6; 
char read_char[200];
String read_string = "";
bool reading;
String co_s,o3_s;
int co,o3;
int i = 0;

int co_x = 96;
int co_y = 0;
int o3_x = 0;
int o3_y = 0;

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
        slave.println(read_string);
        delay(200);
        if(String(read_string[0]) == "2"){
            int i_var = 0;
            co_s = "";
            o3_s = "";
    
            for (int x = 0; x <= read_string.length(); x++) {
                if(String(read_string[x]) == ";" || String(read_string[x]) == "]") {
                    if(String(read_string[x]) == "]") x = 200;
                    i_var++;
                }else {
                    if(i_var == 3) co_s += String(read_string[x]);
                    if(i_var == 4) o3_s += String(read_string[x]);
                }
            }
            dmd.clearScreen();
            Serial.println("OK");
        }
    }
    
    co = co_s.toInt();
    o3 = o3_s.toInt();
    Serial.print(co_s);
    Serial.print(":");
    Serial.println(o3_s);

    co = map(co_s.toInt(), 0, 500, 0, 95);
    dmd.drawFilledBox(co_x,co_y,(co + co_x),(bar_width - 1));//x1,y1,x2,y2

    o3 = map(o3_s.toInt(), 0, 500, 0, 95);
    dmd.drawFilledBox(o3_x,o3_y,(o3 + o3_x),(bar_width - 1));
    delay(100);
}
