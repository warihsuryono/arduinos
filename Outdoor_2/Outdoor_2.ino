#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
SoftwareSerial master(2,3);
const int bar_width = 6;
const int WIDTH = 6; 
char read_char[200];
bool reading;
String pm10_s,so2_s,co_s,o3_s,no2_s;
int pm10,so2,co,o3,no2;
int i = 0;

int pm10_x = 0;
int pm10_y = 384;//384
int so2_x = 0;
int so2_y = 288;//288
int co_x = 0;
int co_y = 192;//192
int o3_x = 0;
int o3_y = 96;//96
int no2_x = 0;
int no2_y = 0;//0

SoftDMD dmd(WIDTH,1);

void setup() {
    Serial.begin(9600);
    master.begin(110);
    dmd.setBrightness(5);
    dmd.begin();
    Serial.println("Begin");
    dmd.drawFilledBox(0,0,191,15);
}

void loop() {
    while (Serial.available()>0){
        if(String(read_char).indexOf("]") <= 0) reading = true;
        read_char[i] = Serial.read();
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
        o3_s = "";
        no2_s = "";

        for (int x = 0; x <= 200; x++) {
            if(String(read_char[x]) == ";" || String(read_char[x]) == "]") {
                if(String(read_char[x]) == "]") x = 200;
                i_var++;
            }else {
                if(i_var == 0) pm10_s += String(read_char[x]);
                if(i_var == 1) so2_s += String(read_char[x]);
                if(i_var == 2) co_s += String(read_char[x]);
                if(i_var == 3) o3_s += String(read_char[x]);
                if(i_var == 4) no2_s += String(read_char[x]);
            }
        }
        dmd.clearScreen();
    }

    pm10 = pm10_s.toInt();
    so2 = so2_s.toInt();
    co = co_s.toInt();
    o3 = o3_s.toInt();
    no2 = no2_s.toInt();
    Serial.print(pm10_s);
    Serial.print(":");
    Serial.print(so2_s);
    Serial.print(":");
    Serial.print(co_s);
    Serial.print(":");
    Serial.print(o3_s);
    Serial.print(":");
    Serial.println(no2_s);

//    if(pm10 > 0){
//        pm10 = map(pm10_s.toInt(), 0, 500, 0, 95);
//        Serial.print("PM10 : ");
//        Serial.println(pm10);
//        dmd.drawFilledBox(pm10_x,pm10_y,pm10,(pm10_y + bar_width -1));//x1,y1,x2,y2
//    }
//    
//    if(so2 > 0){
//        so2 = map(so2, 0, 500, 0, 31);
//        dmd.drawFilledBox(so2_x,so2_y,so2,(so2_y + bar_width -1));
//    }
//
//    if(co > 0){
//        co = map(co, 0, 500, 0, 31);
//        dmd.drawFilledBox(co_x,co_y,co,(co_y + bar_width -1));
//    }
//
//    if(o3 > 0){
//        o3 = map(o3, 0, 500, 0, 31);
//        dmd.drawFilledBox(o3_x,o3_y,o3,(o3_y + bar_width -1));
//    }
//
    if(no2 > 0){
        no2 = map(no2_s.toInt(), 0, 500, 0, 95);
        Serial.print("no2 : ");
        Serial.println(no2);
        dmd.drawFilledBox(no2_x,no2_y,no2,(no2_y + bar_width -1));
    }
    delay(1000);
}
