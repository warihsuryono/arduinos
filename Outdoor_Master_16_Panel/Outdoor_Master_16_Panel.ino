#include <SoftwareSerial.h>

SoftwareSerial textAtas(10,11);
SoftwareSerial textBawah(8,9);
SoftwareSerial graph1(2,3);
SoftwareSerial graph2(5,6);

String read_string = "";

void setup() {
    Serial.begin(2400);
    textAtas.begin(110);
    textBawah.begin(110);
    graph1.begin(110);
    graph2.begin(110);
    Serial.println("Begin");
}

void loop() {
    if(Serial.available() > 0){
        read_string = Serial.readString();
        if(String(read_string[0]) == "1"){
            textAtas.print(read_string);
            Serial.println("OK");
        } else if(String(read_string[0]) == "2"){
            graph1.print(read_string);
            delay(200);
            graph2.print(read_string);
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
            textBawah.print(messages);
            delay(20000);

            messages = "32" + pm10 + ";" + so2 + ";" + co + ";" + o3 + ";" + no2 + "]";
            Serial.print(messages);
            textBawah.print(messages);
            delay(30000);

            messages = "33" + suhu + ";" + tek + ";" + ws + ";" + wd + "]";
            Serial.println(messages);
            textBawah.println(messages);
            Serial.println("OK");
        } else {
            Serial.println("Error");
        }
    }
}
