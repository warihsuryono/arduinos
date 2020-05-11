#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include <fonts/Arial_bold_14.h>
SoftwareSerial master(2,3);
#define DISPLAYS_ACROSS 6
#define DISPLAYS_DOWN 1
char *curr_message = "PT. TRUSUR UNGGUL TEKNUSA";
char *show_message; 
char read_char[200];
String read_string = "";
String text_template = "PM10: {pm10}, SO2: {so2}, CO: {co}, O3: {o3}, NO2: {no2}";
bool reading;
String data;

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD(){ 
    dmd.scanDisplayBySPI();
}

void setup() {
    Serial.begin(9600);
    master.begin(110);
    Timer1.initialize( 5000 );
    Timer1.attachInterrupt( ScanDMD );
    dmd.selectFont(Arial14);
    Serial.println("Begin");
}

String category(String val){
    if(val == "0") return "BAIK";
    else if(val == "1") return "SEDANG";
    else if(val == "2") return "TIDAK SEHAT";
    else if(val == "3") return "SANGAT TIDAK SEHAT";
    else if(val == "4") return "BERBAHAYA";
    else return "";
}

void loop() {
    int i = 0;
    while (master.available()>0){
        delay(10);
        read_char[i] = master.read();
        i++;
    }
    
    if(i > 0){
        Serial.println(read_char);
        String pm10 = category(String(read_char[0]));
        String so2 = category(String(read_char[1]));
        String co = category(String(read_char[2]));
        String o3 = category(String(read_char[3]));
        String no2 = category(String(read_char[4]));
        read_string = " " + text_template + "          ";
        read_string.replace("{pm10}",pm10);
        read_string.replace("{so2}",so2);
        read_string.replace("{co}",co);
        read_string.replace("{o3}",o3);
        read_string.replace("{no2}",no2);
        Serial.println(read_string);
        for (int i = 0; i <= read_string.length(); i++) {
            read_char[i] = read_string[i];
        }
        curr_message = read_char;
    }
    show_message = curr_message;

    if(!reading){
        Serial.print(" ==> ");
        Serial.println(show_message);

         dmd.clearScreen( true );
         dmd.drawMarquee(show_message,strlen(show_message),(32*DISPLAYS_ACROSS)-1,0);
         long start=millis();
         long timer=start;
         boolean ret=false;
         while(!ret){
             if ((timer+30) < millis()) {
                 ret=dmd.stepMarquee(-1,0);
                 timer=millis();
             }
         }
    }
}
