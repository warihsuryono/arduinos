#include <SoftwareSerial.h>

SoftwareSerial text1(2,3);
SoftwareSerial text2(5,6);
SoftwareSerial text3(10,11);

String read_string = "";
String data = "";
int str_length = 0;

void setup() {
    Serial.begin(9600);
    text1.begin(110);
    text2.begin(110);
    text3.begin(110);
}

void loop() {
    if(Serial.available() > 0){
        read_string = Serial.readString();
        str_length = read_string.length();
        data = read_string.substring(1,str_length-1);
        if(String(read_string[0]) == "1"){
            text1.print(data);
            Serial.println("OK");
        } else if(String(read_string[0]) == "2"){
            text2.print(data);
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
            String messages = "1" + outdoor_name + ";" + date_time + "]";
            Serial.print(messages);
            text3.print(messages);
            delay(20000);

            messages = "2" + pm10 + ";" + so2 + ";" + co + ";" + o3 + ";" + no2 + "]";
            Serial.print(messages);
            text3.print(messages);
            delay(30000);

            messages = "3" + suhu + ";" + tek + ";" + ws + ";" + wd + "]";
            Serial.println(messages);
            text3.println(messages);
            Serial.println("OK");
        } else {
            Serial.println("Error");
        }
    }
}
