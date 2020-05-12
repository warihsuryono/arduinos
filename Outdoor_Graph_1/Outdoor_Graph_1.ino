#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
SoftwareSerial master(2,3);
const int bar_width = 16;
const int WIDTH = 6; 
char read_char[200];
bool reading;
String pm10_s,so2_s,co_s;
int pm10,so2,co;
int i = 0;

int pm10_x = 128;
int pm10_y = 0;
int so2_x = 64;
int so2_y = 0;
int co_x = 0;
int co_y = 0;

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
        pm10_s = "";
        so2_s = "";
        co_s = "";

        for (int x = 0; x <= 200; x++) {
            if(String(read_char[x]) == ";" || String(read_char[x]) == "]") {
                if(String(read_char[x]) == "]") x = 200;
                i_var++;
            }else {
                if(i_var == 0) pm10_s += String(read_char[x]);
                if(i_var == 1) so2_s += String(read_char[x]);
                if(i_var == 2) co_s += String(read_char[x]);
            }
        }
        dmd.clearScreen();
    }

    pm10 = pm10_s.toInt();
    so2 = so2_s.toInt();
    co = co_s.toInt();
    Serial.print(pm10_s);
    Serial.print(":");
    Serial.print(so2_s);
    Serial.print(":");
    Serial.println(co_s);

    pm10 = map(pm10_s.toInt(), 0, 500, 0, 63);
    dmd.drawFilledBox(pm10_x,pm10_y,(pm10 + pm10_x),(bar_width - 1));//x1,y1,x2,y2

    so2 = map(so2_s.toInt(), 0, 500, 0, 63);
    dmd.drawFilledBox(so2_x,so2_y,(so2 + so2_x),(bar_width - 1));

    co = map(co_s.toInt(), 0, 500, 0, 63);
    dmd.drawFilledBox(co_x,co_y,(co + co_x),(bar_width - 1));
    delay(1000);
}
