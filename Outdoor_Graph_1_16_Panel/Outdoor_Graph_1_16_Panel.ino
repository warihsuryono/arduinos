#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
SoftwareSerial master(2,3);
const int bar_width = 16;
const int WIDTH = 6; 
char read_char[200];
String read_string = "";
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
    dmd.setBrightness(255);
    dmd.begin();
    Serial.println("Begin");
}

void loop() {
    if(master.available() > 0){
        read_string = master.readString();
        Serial.print(read_string);
        if(String(read_string[0]) == "2"){
            int i_var = 0;
            pm10_s = "";
            so2_s = "";
            co_s = "";
    
            for (int x = 0; x <= read_string.length(); x++) {
                if(String(read_string[x]) == ";" || String(read_string[x]) == "]") {
                    if(String(read_string[x]) == "]") x = 200;
                    i_var++;
                }else {
                    if(i_var == 1) pm10_s += String(read_string[x]);
                    if(i_var == 2) so2_s += String(read_string[x]);
                    if(i_var == 3) co_s += String(read_string[x]);
                }
            }
            dmd.clearScreen();
            Serial.println("OK");
        }
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
