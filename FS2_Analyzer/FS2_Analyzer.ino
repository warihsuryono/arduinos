#include <SoftwareSerial.h>
SoftwareSerial pm25(10,11);
SoftwareSerial pm10(8,9);

String read_string_pm25 = "";
String read_string_pm10 = "";
String string_pm25 = "";
String string_pm10 = "";
int try_pm25 = 0;
int try_pm10 = 0;

int sensor1 = A0;
int sensor2 = A1;
int val1 = 0;
int val2 = 0;

void setup() {
    Serial.begin(9600);
    pm25.begin(9600);
    pm10.begin(9600);
    delay(1000);
}

String getValue(String data)
{
    String retval = "";
    if(data.length() > 0){
      int comas = 0;
      for(int i=0;i<data.length() - 1;i++){
        if(comas < 2 && data[i] != ','){
          retval += data[i];
        } else {
          if(comas < 1) retval += ";";
          comas++;
        }
      }
    }
    return retval;
}

void read_pm25(){
    try_pm25 = 0;
    // string_pm25 = "";
    read_string_pm25 = "";
    pm25.listen();
    delay(1000);
    while(pm25.available() <= 0){
      try_pm25++;
      if(try_pm25 > 200) break;
    }
    if(pm25.available() > 0){
      while(pm25.available() > 0){
        char pm25_read = pm25.read();
        read_string_pm25 += pm25_read;
        if(pm25_read == 13){
          string_pm25 = read_string_pm25;
          break;
        }
      }  
    }
}

void read_pm10(){
    try_pm10 = 0;
    // string_pm10 = "";
    read_string_pm10 = "";
    pm10.listen();
    delay(1000);
    while(pm10.available() <= 0){
      try_pm10++;
      if(try_pm10 > 200) break;
    }
    if(pm10.available() > 0){
      while(pm10.available() > 0){
        char pm10_read = pm10.read();
        read_string_pm10 += pm10_read;
        if(pm10_read == 13){
          string_pm10 = read_string_pm10;
          break;
        }
      }  
    }
}

void loop() {
    val1 = analogRead(sensor1);
    val2 = analogRead(sensor2);
    read_pm25();
    Serial.println("METONE;" + getValue(string_pm25) + ";" + getValue(string_pm10) + ";" + val1 + ";" + val2 + ";");
    read_pm10();
    Serial.println("METONE;" + getValue(string_pm25) + ";" + getValue(string_pm10) + ";" + val1 + ";" + val2 + ";");
}
