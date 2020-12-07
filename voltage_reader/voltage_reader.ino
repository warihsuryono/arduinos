#include <Wire.h>
#include <Ard2499.h>
Ard2499 ard2499board;

void setup() {
  Serial.begin(9600);
  Wire1.begin();
  ard2499board.begin(ARD2499_ADC_ADDR_ZZZ, ARD2499_EEP_ADDR_ZZ);
  ard2499board.ltc2499ChangeConfiguration(LTC2499_CONFIG2_60_50HZ_REJ);
}

int32_t AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7;
int32_t AVG_AIN0, AVG_AIN1, AVG_AIN2, AVG_AIN3, AVG_AIN4, AVG_AIN5, AVG_AIN6, AVG_AIN7;
int counter = 0;

void loop() {

  AIN0 = AIN0 + ard2499board.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_1P);
  AIN1 = AIN1 + ard2499board.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_2P);
  AIN2 = AIN2 + ard2499board.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_3P);
  AIN3 = AIN3 + ard2499board.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_4P);
  //AIN4 = AIN4 + ard2499board.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_5P);
  //AIN5 = AIN5 + ard2499board.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_6P);
  //AIN6 = AIN6 + ard2499board.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_7P);
  //AIN7 = AIN7 + ard2499board.ltc2499ReadAndChangeChannel(LTC2499_CHAN_SINGLE_8P);

  //Serial.println(String((AIN0*2.048/16777216), 6) + ";" + String((AIN1*2.048/16777216), 6) + ";" + String((AIN2*2.048/16777216), 6) + ";" + String((AIN3*2.048/16777216), 6) + ";" + String((AIN4*2.048/16777216), 6) + ";" + String((AIN5*2.048/16777216), 6) + ";" + String((AIN6*2.048/16777216), 6) + ";" + String((AIN7*2.048/16777216), 6) + ";");

  counter++;
  if(counter >= 30){
    AVG_AIN0 = AIN0 / counter;
    AVG_AIN1 = AIN1 / counter;
    AVG_AIN2 = AIN2 / counter;
    AVG_AIN3 = AIN3 / counter;
    //AVG_AIN4 = AIN4 / counter;
    //AVG_AIN5 = AIN5 / counter;
    //AVG_AIN6 = AIN6 / counter;
    //AVG_AIN7 = AIN7 / counter;
    AIN0 = 0;
    AIN1 = 0;
    AIN2 = 0;
    AIN3 = 0;
    //AIN4 = 0;
    //AIN5 = 0;
    //AIN6 = 0;
    //AIN7 = 0;
    counter = 0;
  }
  Serial.println(String((AVG_AIN0*2.048/16777216), 6) + ";" + String((AVG_AIN1*2.048/16777216), 6) + ";" + String((AVG_AIN2*2.048/16777216), 6) + ";" + String((AVG_AIN3*2.048/16777216), 6) + ";" + String((AVG_AIN4*2.048/16777216), 6) + ";" + String((AVG_AIN5*2.048/16777216), 6) + ";" + String((AVG_AIN6*2.048/16777216), 6) + ";" + String((AVG_AIN7*2.048/16777216), 6) + ";");
    
}
