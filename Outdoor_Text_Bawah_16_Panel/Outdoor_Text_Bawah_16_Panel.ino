#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include <fonts/Droid_Sans_12.h>
SoftwareSerial master(4,5);
const int WIDTH = 3;
const String text_template_1 = "Stasiun _a: _b ";
const String text_template_2 = "PM10:_a SO2:_b CO:_c O3:_d NO2:_e ";
const String text_template_3 = "SUHU:_aC TEK:_bmBar WS: _cm/s WD:_d";
String read_string = "";
String read_string_1 = "PT. TRUSUR UNGGUL TEKNUSA";
String read_string_2 = "";
String read_string_3 = "";
bool reading;
String data;
String outdoor_name,date_time,pm10,so2,co,o3,no2,suhu,tek,ws,wd;
int i = 0;
int speedmarquee = 30;

DMD dmd(WIDTH,1);
void ScanDMD(){ 
    dmd.scanDisplayBySPI();
}

void setup() {
    Serial.begin(9600);
    master.begin(110);
    Timer1.initialize( 5000 );
    Timer1.attachInterrupt( ScanDMD );
    dmd.selectFont(Droid_Sans_12);
    Serial.println("Begin");
}

void loop() {
    if(master.available() > 0){
        read_string = master.readString();
        Serial.print(read_string);
        delay(200);
        if(String(read_string[0]) == "3"){
            int i_var = 0;
            int i_char = 0;
            if(String(read_string[1]) == "1"){
                outdoor_name = "";
                date_time = "";
            }
            if(String(read_string[1]) == "2"){
                pm10 = "";
                so2 = "";
                co = "";
                o3 = "";
                no2 = "";
            }
            if(String(read_string[1]) == "3"){
                suhu = "";
                tek = "";
                ws = "";
                wd = "";
            }
            for (int x = 2; x <= read_string.length(); x++) {
                if(String(read_string[x]) == ";" || String(read_string[x]) == "]") {
                    if(String(read_string[x]) == "]") x = 200;
                    i_var++;
                }else {
                    if(String(read_string[1]) == "1"){
                        if(i_var == 0) outdoor_name += String(read_string[x]);
                        if(i_var == 1) date_time += String(read_string[x]);
                    }
                    if(String(read_string[1]) == "2"){
                        if(i_var == 0) pm10 += String(read_string[x]);
                        if(i_var == 1) so2 += String(read_string[x]);
                        if(i_var == 2) co += String(read_string[x]);
                        if(i_var == 3) o3 += String(read_string[x]);
                        if(i_var == 4) no2 += String(read_string[x]);
                    }
                    if(String(read_string[1]) == "3"){
                        if(i_var == 0) suhu += String(read_string[x]);
                        if(i_var == 1) tek += String(read_string[x]);
                        if(i_var == 2) ws += String(read_string[x]);
                        if(i_var == 3) wd += String(read_string[x]);
                    }
                }
            }
            if(String(read_string[1]) == "1"){
                read_string_1 = text_template_1;
                read_string_1.replace("_a",outdoor_name);
                read_string_1.replace("_b",date_time);
                Serial.println(read_string_1);
            }
            if(String(read_string[1]) == "2"){
                read_string_2 = text_template_2;
                read_string_2.replace("_a",pm10);
                read_string_2.replace("_b",so2);
                read_string_2.replace("_c",co);
                read_string_2.replace("_d",o3);
                read_string_2.replace("_e",no2);
                Serial.println(read_string_2);
            }
            if(String(read_string[1]) == "3"){       
                read_string_3 = text_template_3;
                read_string_3.replace("_a",suhu);
                read_string_3.replace("_b",tek);
                read_string_3.replace("_c",ws);
                read_string_3.replace("_d",wd);
                Serial.println(read_string_3);
            }
            Serial.println("OK");
        }
    }
    

    String show_message = read_string_1;
    show_message.concat(read_string_2);
    Serial.print(" ==> ");
    Serial.print(read_string_1);
    Serial.print(read_string_2);
    Serial.println(read_string_3);

    dmd.clearScreen( true );
    dmd.drawMarquee(read_string_1.c_str(),strlen(read_string_1.c_str()),(32*WIDTH)-1,3);
    long start=millis();
    long timer=start;
    boolean ret=false;
    while(!ret){
        if ((timer+speedmarquee) < millis()) {
          ret=dmd.stepMarquee(-1,0);
          timer=millis();
        }
    }

    dmd.clearScreen( true );
    dmd.drawMarquee(read_string_2.c_str(),strlen(read_string_2.c_str()),(32*WIDTH)-1,3);
    start=millis();
    timer=start;
    ret=false;
    while(!ret){
        if ((timer+speedmarquee) < millis()) {
          ret=dmd.stepMarquee(-1,0);
          timer=millis();
        }
    }

    dmd.clearScreen( true );
    dmd.drawMarquee(read_string_3.c_str(),strlen(read_string_3.c_str()),(32*WIDTH)-1,3);
    start=millis();
    timer=start;
    ret=false;
    while(!ret){
        if ((timer+speedmarquee) < millis()) {
          ret=dmd.stepMarquee(-1,0);
          timer=millis();
        }
    }
    
    delay(200);
}
