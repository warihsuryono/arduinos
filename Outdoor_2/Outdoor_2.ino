#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
SoftwareSerial master(2,3);
const int WIDTH = 1; 
char read_char[200];
String read_string_1 = "";
String read_string_2 = "";
bool reading;
String data;
String pm10,so2,co,o3,no2;
int i = 0;

SoftDMD dmd(WIDTH,1);

void setup() {
    Serial.begin(9600);
    master.begin(110);
    dmd.setBrightness(255);
    dmd.begin();
    Serial.println("Begin");
}

void loop() {
    /*while (master.available()>0){
        reading = true;
        read_char[i] = master.read();
        if(String(read_char[i]) == "]") reading = false;
        i++;
    }
    
    if(i > 0 && !reading){
        i = 0;
        int i_var = 0;
        int i_char = 0;
        pm10 = "";
        so2 = "";
        co = "";
        o3 = "";
        no2 = "";

        for (int x = 1; x <= 200; x++) {
            if(String(read_char[x]) == ";" || String(read_char[x]) == "]") {
                if(String(read_char[x]) == "]") x = 200;
                i_var++;
                i_char = 0;
            }else {
                if(i_var == 0) pm10 += String(read_char[x]);
                if(i_var == 1) so2 += String(read_char[x]);
                if(i_var == 2) co += String(read_char[x]);
                if(i_var == 3) o3 += String(read_char[x]);
                if(i_var == 4) no2 += String(read_char[x]);
                i_char++;
            }
        }
    }*/


    //y1=titik paling bawah
    //y2=tinggi
    dmd.drawFilledBox(0,15,4,8);//x1,y1,x2,y2
    dmd.drawFilledBox(6,15,10,4);
    dmd.drawFilledBox(12,15,16,6);
    dmd.drawFilledBox(18,15,22,0);
    dmd.drawFilledBox(24,15,28,2);
    
}
