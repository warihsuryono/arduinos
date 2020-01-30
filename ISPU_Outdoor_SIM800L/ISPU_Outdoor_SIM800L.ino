#include <SoftwareSerial.h>
String Arsp, Grsp, returnVal,IMSI;
int steps = 0;
String commands[13];
bool wSerial = true;
int delimiter_1, delimiter_2;
SoftwareSerial gsm(4, 5); // RX, TX
void setup() {
  pinMode(13, OUTPUT);
  commands[0] = "AT";
  commands[1] = "AT+CIMI";
  commands[2] = "AT+CSQ";
  commands[3] = "AT+CFUN=1";
  commands[4] = "AT+CPIN?";
  commands[5] = "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";
  commands[6] = "AT+SAPBR=3,1,\"APN\",\"internet\"";
  commands[7] = "AT+SAPBR=1,1";
  commands[8] = "AT+HTTPINIT";
  commands[9] = "AT+HTTPPARA=\"CID\",1";
  commands[10] = "AT+HTTPPARA=\"URL\",\"http://trusur-ispudev.ddns.net:1989/api/outdoor.php?imsi=";
  commands[11] = "AT+HTTPACTION=0";
  commands[12] = "AT+HTTPREAD";
  if(wSerial) Serial.begin(9600);
  delay(2000);
  gsm.begin(1200);//110,300,1200,2400,4800
  if(wSerial) Serial.println("Start!");
  while(!gsm){}
  if(gsm.available() || true){
    gsm.println(commands[steps]);
    if(wSerial) Serial.println(commands[steps]);
  }
}

void blink(){
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
}

void loop() {
  if(steps == 0){
    if(gsm.available()){
      blink();
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        steps = 1;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);  
      }
    }
  }
  if(steps == 1){
    if(gsm.available()){
      blink();
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
		    delimiter_1 = Grsp.indexOf("\n") + 1;
        delimiter_2 = Grsp.indexOf("\n", delimiter_1);
        IMSI = Grsp.substring(delimiter_1, delimiter_2 - 1);
        if(wSerial) Serial.println("IMSI : " + IMSI);
        steps = 2;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);  
      }
    }
  }
  if(steps == 2){
    if(gsm.available()){
      blink();
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("CSQ: 0,0") > 0){
        //steps = 2;
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);  
      } else if(Grsp.indexOf("CSQ: ") > 0){
        digitalWrite(13, HIGH);
        steps = 3;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 3){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        steps = 4;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 4){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        steps = 5;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else if(Grsp.indexOf("ERROR") > 0){
        steps = 2;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 5){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        steps = 6;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 6){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        steps = 7;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 7){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0 || Grsp.indexOf("ERROR") > 0){
        steps = 8;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 8){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        steps = 9;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 9){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        steps = 10;
        gsm.println(commands[steps]+IMSI+"\"");
        if(wSerial) Serial.println(commands[steps]);
      } else if(Grsp.indexOf("ERROR") > 0){
        steps = 2;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 10){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        steps = 11;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else if(Grsp.indexOf("ERROR") > 0){
        steps = 2;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]+IMSI+"\"");
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 11){
    if(gsm.available()){
      delay(2000);
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("+HTTPACTION:") > 0 && Grsp.indexOf(",200,") > 0){
        steps = 12;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else if(Grsp.indexOf("+HTTPACTION:") > 0 && Grsp.indexOf(",604,") > 0){
        steps = 9;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else if(Grsp.indexOf("ERROR") > 0){
        steps = 2;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(3000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
  if(steps == 12){
    if(gsm.available()){
      Grsp = gsm.readString();
      if(wSerial) Serial.println(Grsp);
      if(Grsp.indexOf("OK") > 0){
        delimiter_1 = Grsp.indexOf("\n", Grsp.indexOf("\n") + 1) + 1;
        delimiter_2 = Grsp.indexOf("\n", delimiter_1);
        returnVal = Grsp.substring(delimiter_1, delimiter_2);
        if(wSerial) Serial.println("Http Return : " + returnVal);
        delay(20000);
        steps = 9;
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      } else {
        delay(1000);
        gsm.println(commands[steps]);
        if(wSerial) Serial.println(commands[steps]);
      }
    }
  }
}
