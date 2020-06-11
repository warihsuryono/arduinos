#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
SoftwareSerial slave(2,3);
const int bar_width = 16;
const int WIDTH = 6; 
char read_char[200];
String read_string = "";
bool reading;
String pm10_s,so2_s;
int pm10,so2;
int i = 0;

int pm10_x = 96;
int pm10_y = 0;
int so2_x = 0;
int so2_y = 0;

SoftDMD dmd(WIDTH,1);

void setup() {
    Serial.begin(2400);
    slave.begin(110);
    dmd.setBrightness(255);
    dmd.begin();
    Serial.println("Begin");
}

void loop() {
    if(Serial.available() > 0){
        read_string = Serial.readString();
        Serial.print(read_string);
        if(String(read_string[0]) == "2"){
            slave.println(read_string);
            delay(200);
            int i_var = 0;
            pm10_s = "";
            so2_s = "";
    
            for (int x = 0; x <= read_string.length(); x++) {
                if(String(read_string[x]) == ";" || String(read_string[x]) == "]") {
                    if(String(read_string[x]) == "]") x = 200;
                    i_var++;
                }else {
                    if(i_var == 1) pm10_s += String(read_string[x]);
                    if(i_var == 2) so2_s += String(read_string[x]);
                }
            }
            dmd.clearScreen();
            Serial.println("OK");
        } else if(String(read_string[0]) == "3"){
            int i_var = 0;
            String outdoor_name,date_time,pm10,so2,co,o3,no2,suhu,tek,ws,wd;
            outdoor_name = "";
            date_time = "";
            pm10 = "";
            so2 = "";
            co = "";
            o3 = "";
            no2 = "";
            suhu = "";
            tek = "";
            ws = "";
            wd = "";
            for (int x = 1; x <= read_string.length(); x++) {
                if(String(read_string[x]) == ";" || String(read_string[x]) == "]") {
                    i_var++;
                } else {
                    if(i_var == 0) outdoor_name += read_string[x];
                    if(i_var == 1) date_time += read_string[x];
                    if(i_var == 2) pm10 += read_string[x];
                    if(i_var == 3) so2 += read_string[x];
                    if(i_var == 4) co += read_string[x];
                    if(i_var == 5) o3 += read_string[x];
                    if(i_var == 6) no2 += read_string[x];
                    if(i_var == 7) suhu += read_string[x];
                    if(i_var == 8) tek += read_string[x];
                    if(i_var == 9) ws += read_string[x];
                    if(i_var == 10) wd += read_string[x];
                }
            }
            String messages = "31" + outdoor_name + ";" + date_time + "]";
            Serial.print(messages);
            slave.print(messages);
            delay(20000);

            messages = "32" + pm10 + ";" + so2 + ";" + co + ";" + o3 + ";" + no2 + "]";
            Serial.print(messages);
            slave.print(messages);
            delay(30000);

            messages = "33" + suhu + ";" + tek + ";" + ws + ";" + wd + "]";
            Serial.println(messages);
            slave.println(messages);
            Serial.println("OK");
        } else {
            slave.println(read_string);
            delay(200);
        }
    }
    
    pm10 = pm10_s.toInt();
    so2 = so2_s.toInt();
    Serial.print(pm10_s);
    Serial.print(":");
    Serial.println(so2_s);

    pm10 = map(pm10_s.toInt(), 0, 500, 0, 95);
    dmd.drawFilledBox(pm10_x,pm10_y,(pm10 + pm10_x),(bar_width - 1));//x1,y1,x2,y2

    so2 = map(so2_s.toInt(), 0, 500, 0, 95);
    dmd.drawFilledBox(so2_x,so2_y,(so2 + so2_x),(bar_width - 1));
    delay(100);
}
