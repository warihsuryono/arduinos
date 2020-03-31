#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial_bold_14.h>
SoftwareSerial master(2,3);
const int WIDTH = 3;
char *curr_message_1 = "PT. TRUSUR UNGGUL TEKNUSA";
char *curr_message_2 = "          ";
char *show_message_1; 
char *show_message_2; 
char read_char[200];
String read_string_1 = "";
String read_string_2 = "";
String text_template_1 = "Stasiun {outdoor_name}: {date_time} PM10:{pm10} SO2:{so2} CO:{co} O3:{o3} NO2:{no2}";
String text_template_2 = "SUHU:{suhu}C TEK:{tek}mBar WS: {ws}m/s WD:{wd}";
bool reading;
String data;
String outdoor_name,date_time,pm10,so2,co,o3,no2,suhu,tek,ws,wd;
int i = 0;

SoftDMD dmd(WIDTH,1);
DMD_TextBox box(dmd,0,1,32 * WIDTH,0);//L,T,W,H

void setup() {
    Serial.begin(9600);
    master.begin(110);
    dmd.setBrightness(255);
    dmd.selectFont(Arial14);
    dmd.begin();
    Serial.println("Begin");
}

void loop() {
    while (master.available()>0){
        reading = true;
        read_char[i] = master.read();
        if(String(read_char[i]) == "]") reading = false;
        i++;
    }
    
    if(i > 0 && !reading){
        i = 0;
        int i_var = 0;
        int i_char = 0;
        if(String(read_char[0]) == "1"){
            outdoor_name = "";
            date_time = "";
            pm10 = "";
            so2 = "";
            co = "";
            o3 = "";
            no2 = "";
        }
        if(String(read_char[0]) == "2"){
            suhu = "";
            tek = "";
            ws = "";
            wd = "";
        }
        for (int x = 1; x <= 200; x++) {
            if(String(read_char[x]) == ";" || String(read_char[x]) == "]") {
                if(String(read_char[x]) == "]") x = 200;
                i_var++;
                i_char = 0;
            }else {
                if(String(read_char[0]) == "1"){
                    if(i_var == 0) outdoor_name += String(read_char[x]);
                    if(i_var == 1) date_time += String(read_char[x]);
                    if(i_var == 2) pm10 += String(read_char[x]);
                    if(i_var == 3) so2 += String(read_char[x]);
                    if(i_var == 4) co += String(read_char[x]);
                    if(i_var == 5) o3 += String(read_char[x]);
                    if(i_var == 6) no2 += String(read_char[x]);
                }
                if(String(read_char[0]) == "2"){
                    if(i_var == 0) suhu += String(read_char[x]);
                    if(i_var == 1) tek += String(read_char[x]);
                    if(i_var == 2) ws += String(read_char[x]);
                    if(i_var == 3) wd += String(read_char[x]);
                }
                i_char++;
            }
        }
        if(String(read_char[0]) == "1"){
            read_string_1 = " " + text_template_1 + " ";
            read_string_1.replace("{outdoor_name}",outdoor_name);
            read_string_1.replace("{date_time}",date_time);
            read_string_1.replace("{pm10}",pm10);
            read_string_1.replace("{so2}",so2);
            read_string_1.replace("{co}",co);
            read_string_1.replace("{o3}",o3);
            read_string_1.replace("{no2}",no2);
            Serial.println(read_string_1);
            curr_message_1 = read_string_1.c_str();
            Serial.print(" => ");
            Serial.println(curr_message_1);
        }
        if(String(read_char[0]) == "2"){       
            read_string_2 = " " + text_template_2 + "          ";
            read_string_2.replace("{suhu}",suhu);
            read_string_2.replace("{tek}",tek);
            read_string_2.replace("{ws}",ws);
            read_string_2.replace("{wd}",wd);
            Serial.println(read_string_2);
            curr_message_2 = read_string_2.c_str();
            Serial.print(" => ");
            Serial.println(curr_message_2);
        }
    }
    show_message_1 = curr_message_1;
    show_message_2 = curr_message_2;
    
    Serial.print(" ==> ");
    Serial.println(show_message_1);
    Serial.print(" ==> ");
    Serial.println(show_message_2);
    while(*show_message_1) {
        box.print(*show_message_1);
        delay(100);
        *show_message_1++;
    }    
    while(*show_message_2) {
        box.print(*show_message_2);
        delay(100);
        *show_message_2++;
    }
}
