#include <SoftwareSerial.h>
String Arsp, Grsp, returnVal, IMSI;
byte req;
int steps = 0;
int i = 0;
long interval = 20000;
unsigned long currentMillis=0;	
unsigned long previousMillis=0;
String commands[14];
bool wSerial = true;
int delimiter_1, delimiter_2, error_num;
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
	error_num = 0;
	returnVal = "0";
	Serial.begin(9600);
	gsm.begin(1200);//110,300,1200,2400,4800
	if(wSerial) Serial.println("Start!");
	while(!gsm){}
	if(gsm.available() || true){
		gsm.println(commands[steps]);
		if(wSerial) Serial.println(commands[steps]);
	}
}

void response(){
	if(Serial.available()){
		req = Serial.read();
		if(req == 114) Serial.println(returnVal);
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

void fastblink(){
	for(i=0;i<20;i++){
		digitalWrite(13, HIGH);
		delay(25);
		digitalWrite(13, LOW);
		delay(25);
	}
	digitalWrite(13, HIGH);
}

void loop() {
	if(gsm.available()){
		if(steps == 0 || steps == 3 || steps == 5 || steps == 6 || steps == 12){
			Grsp = gsm.readString();
			delay(500);
			if(steps == 0){ blink(); }
			if(wSerial) Serial.println(Grsp);
			if(Grsp.indexOf("OK") > 0){
				error_num=0;
				steps++;
				if(steps == 13){
					delimiter_1 = Grsp.indexOf("|||") + 1;
					delimiter_2 = Grsp.indexOf("|||", delimiter_1);
					returnVal = "|" + Grsp.substring(delimiter_1, delimiter_2 - 1) + "|||";
					unsigned long currentMillis = millis();
					previousMillis = currentMillis;
					fastblink();
					if(wSerial) Serial.println("WriteData : " + returnVal);
				} else {
					gsm.println(commands[steps]);
					if(wSerial) Serial.println(commands[steps]);
				}
			} else {
				delay(1000);
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			}
		}
		if(steps == 1){
			Grsp = gsm.readString();
			delay(500);
			blink();
			if(wSerial) Serial.println(Grsp);
			if(Grsp.indexOf("OK") > 0){
				error_num=0;
				steps++;
				delimiter_1 = Grsp.indexOf("\n") + 1;
				delimiter_2 = Grsp.indexOf("\n", delimiter_1);
				IMSI = Grsp.substring(delimiter_1, delimiter_2 - 1);
				if(wSerial) Serial.println("IMSI : " + IMSI);
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			} else if(Grsp.indexOf("ERROR") > 0){
				error_num++;
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			} else {
				delay(1000);
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);  
			}
		}
		if(steps == 2){
			Grsp = gsm.readString();
			delay(500);
			blink();
			if(wSerial) Serial.println(Grsp);
			if(Grsp.indexOf("CSQ: 0,0") > 0){
				error_num++;
				delay(1000);
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);  
			} else if(Grsp.indexOf("CSQ: ") > 0){
				error_num=0;
				steps++;
				digitalWrite(13, HIGH);
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			} else {
				delay(1000);
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			}
		}
		if(steps == 4 || steps == 7 || steps == 8 || steps == 9 || steps == 10){
			Grsp = gsm.readString();
			delay(500);
			if(wSerial) Serial.println(Grsp);
			if(Grsp.indexOf("OK") > 0){
				error_num=0;
				steps++;
				if(steps == 10){
					gsm.println(commands[steps]+IMSI+"\"");
					if(wSerial) Serial.println(commands[steps]+IMSI+"\"");
				} else {
					gsm.println(commands[steps]);
					if(wSerial) Serial.println(commands[steps]);
				}
			} else if(Grsp.indexOf("ERROR") > 0){
				error_num++;
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			} else {
				delay(1000);
				if(steps == 10){
					gsm.println(commands[steps]+IMSI+"\"");
					if(wSerial) Serial.println(commands[steps]+IMSI+"\"");
				} else {
					gsm.println(commands[steps]);
					if(wSerial) Serial.println(commands[steps]);
				}
			}
		}
		if(steps == 11){
			delay(2000);
			Grsp = gsm.readString();
			delay(500);
			if(wSerial) Serial.println(Grsp);
			if(Grsp.indexOf("+HTTPACTION:") > 0 && Grsp.indexOf(",200,") > 0){
				error_num=0;
				steps++;
				delay(3000);
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			} else if(Grsp.indexOf("+HTTPACTION:") > 0 && Grsp.indexOf(",604,") > 0){
				error_num++;
				steps = 9;
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			} else if(Grsp.indexOf("ERROR") > 0){
				error_num++;
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			} else {
				delay(1000);
				gsm.println(commands[steps]);
				if(wSerial) Serial.println(commands[steps]);
			}
		}
	} else {
		error_num++;
	}
	if(steps == 13){
		unsigned long currentMillis = millis();
		if ((unsigned long)(currentMillis - previousMillis) >= interval){
			steps = 9;
			gsm.println(commands[steps]);
			if(wSerial) Serial.println(commands[steps]);
		}
	}
	response();
	if(error_num > 5) {}
}
