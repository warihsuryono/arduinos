#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

int sensor0 = A0;
int sensor1 = A1;
char readsensor0[5] = "";
char readsensor1[5] = "";
char msg[9];
String datatosend = "";
String digit4 = "0000";

void setup()
{
    pinMode(13, OUTPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    driver.init();
    //Serial.begin(9600);
    //if (!driver.init()) Serial.println("init failed");
}

void loop()
{
    itoa(analogRead(sensor0), readsensor0, 10);
    itoa(analogRead(sensor1), readsensor1, 10);
    datatosend = digit4.substring(0,(4-strlen(readsensor0))) + readsensor0;
    datatosend = datatosend + digit4.substring(0,(4-strlen(readsensor1))) + readsensor1;
    datatosend.toCharArray(msg, 9);
    Serial.println(msg);
    digitalWrite(13, HIGH);
    driver.send((uint8_t *)msg, strlen(msg));
    //driver.waitPacketSent();
    digitalWrite(13, LOW);
    delay(300);
}
