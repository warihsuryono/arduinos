#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <Wire.h>

RH_ASK driver;
int sensor0 = 512,sensor1 = 512,throttle=0,x_throttle=0,y_throttle=0;
int mod_throttle[256];
int nosignal_i = 0,x_nosignal_i = 0;
int pinBackward = 7;
int pinThrottle = 6;
int i_modulus = 0;
int max_sampling = 20;
int i_throttle[20];
int ii = 0;
bool isNoSignal = false,xisNoSignal = false;
bool isForward = true;

void setup()
{
    pinMode(pinBackward, OUTPUT);
    pinMode(pinThrottle, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(pinBackward, LOW);
    analogWrite(pinThrottle, 0);
    digitalWrite(4, HIGH);
    isForward = true;
    driver.init();
    Serial.begin(9600);
    Wire.begin();
}

void loop()
{
    digitalWrite(13, HIGH);
    uint8_t buf[8];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)){
      isNoSignal = false;
      x_nosignal_i = 0;
      sensor0 = String((char*)buf).substring(0,4).toInt();
      sensor1 = String((char*)buf).substring(4,8).toInt();
    } else {
      nosignal_i++;
      if(nosignal_i > 50){
        nosignal_i = 0;
        isNoSignal = true;
        x_nosignal_i = 0;
      }
      if(isNoSignal){
        x_nosignal_i++;
        if(x_nosignal_i > 50){
          x_nosignal_i = 0;
          sensor0 = 512;
          sensor1 = 512;
        }
      }
    }
    digitalWrite(13, LOW);
    Wire.beginTransmission(8);
    Wire.write(map(sensor1, 0, 1023, 0, 180));
    Wire.endTransmission();
    y_throttle = map(sensor0, 0, 890, 0, 255);
    if(i_modulus < max_sampling){
      if(sensor0 != 512){
        if(mod_throttle[y_throttle] <= 0){
          i_throttle[ii] = y_throttle;
          mod_throttle[y_throttle] = 0;
          ii++;
        }
        mod_throttle[y_throttle]++;
        i_modulus++;
      }
    }
    if(i_modulus >= max_sampling){
      throttle = 0;
      ii = 0;
      i_modulus = 0;

      for (int xx = 0; xx < max_sampling; xx++){
        throttle = (mod_throttle[i_throttle[xx]] > mod_throttle[throttle]) ? i_throttle[xx] : throttle;
        mod_throttle[i_throttle[xx]] = 0;
        i_throttle[xx] = 0;
      }
      mod_throttle[throttle] = 0;
      
      if(throttle >= 130){
        if(isForward == false){
          isForward = true;
          analogWrite(pinThrottle, 0);
          delay(500);
        }
        digitalWrite(pinBackward, LOW);
        x_throttle = map(throttle, 130, 245, 127, 255);
      } else if(throttle <= 60){
        if(isForward == true){
          isForward = false;
          analogWrite(pinThrottle, 0);
          delay(500);
        }
        digitalWrite(pinBackward, HIGH);
        x_throttle = map(throttle, 60, 0, 127, 255);
      } else {
        isForward = true;
        digitalWrite(pinBackward, LOW);
        x_throttle = 0;
      }
      if(x_throttle > 255) x_throttle = 255;
      analogWrite(pinThrottle, x_throttle);
      
      //Serial.println(x_throttle);
    }
}
