#include <SoftwareSerial.h>
#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include <fonts/Droid_Sans_12.h>
SoftwareSerial master(2,3);
#define DISPLAYS_ACROSS 3
#define DISPLAYS_DOWN 1
char *curr_message = "PT. TRUSUR UNGGUL TEKNUSA";
char *show_message; 
char read_char[200];
String read_string = "";
String text_template = "PM10: {pm10}, SO2: {so2}, CO: {co}, O3: {o3}, NO2: {no2}";
bool reading;
int speedmarquee = 30;

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

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

String category(String val){
    if(val == "0") return "BAIK";
    else if(val == "1") return "SEDANG";
    else if(val == "2") return "TIDAK SEHAT";
    else if(val == "3") return "SANGAT TIDAK SEHAT";
    else if(val == "4") return "BERBAHAYA";
    else return "";
}

void loop() {
    if(master.available() > 0){
        read_string = master.readString();
        Serial.print(read_string);
        delay(200);
        if(String(read_string[0]) == "1"){
            String pm10 = category(String(read_string[1]));
            String so2 = category(String(read_string[2]));
            String co = category(String(read_string[3]));
            String o3 = category(String(read_string[4]));
            String no2 = category(String(read_string[5]));
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
            Serial.println("OK");
        } else {
            Serial.println("Error");
        }
    }

    show_message = curr_message;
    Serial.print(" ==> ");
    Serial.println(show_message);
    dmd.clearScreen( true );
    dmd.drawMarquee(show_message,strlen(show_message),(32*DISPLAYS_ACROSS)-1,3);
    long start=millis();
    long timer=start;
    boolean ret=false;
    while(!ret){
       if ((timer+speedmarquee) < millis()) {
           ret=dmd.stepMarquee(-1,0);
           timer=millis();
       }
    }
    delay(100);
}
