#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
SoftwareSerial master(2,3);
const int bar_width = 16;
const int WIDTH = 4; 
char read_char[200];
bool reading;
String o3_s,no2_s;
int o3,no2;
int i = 0;

int o3_x = 64;
int o3_y = 0;
int no2_x = 0;
int no2_y = 0;

SoftDMD dmd(WIDTH,1);

void setup() {
    Serial.begin(9600);
    master.begin(110);
    dmd.setBrightness(5);
    dmd.begin();
    Serial.println("Begin");
}

void loop() {
    while (master.available()>0){
        if(String(read_char).indexOf("]") <= 0) reading = true;
        read_char[i] = master.read();
        if(String(read_char[i]) == "]") reading = false;
        i++;
        delay(20);
    }
    
    if(i > 0 && !reading){
        i = 0;
        int i_var = 0;
        o3_s = "";
        no2_s = "";

        for (int x = 0; x <= 200; x++) {
            if(String(read_char[x]) == ";" || String(read_char[x]) == "]") {
                if(String(read_char[x]) == "]") x = 200;
                i_var++;
            }else {
                if(i_var == 3) o3_s += String(read_char[x]);
                if(i_var == 4) no2_s += String(read_char[x]);
            }
        }
        dmd.clearScreen();
    }

   
    o3 = o3_s.toInt();
    no2 = no2_s.toInt();
    Serial.print(o3_s);
    Serial.print(":");
    Serial.println(no2_s);

    o3 = map(o3_s.toInt(), 0, 500, 0, 63);
    dmd.drawFilledBox(o3_x,o3_y,(o3 + o3_x),(bar_width - 1));//x1,y1,x2,y2

    no2 = map(no2_s.toInt(), 0, 500, 0, 63);
    dmd.drawFilledBox(no2_x,no2_y,(no2 + no2_x),(bar_width - 1));
    
    delay(1000);
}
