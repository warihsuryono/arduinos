/*************************************************************************
Title:    ARD-LTC2499 Library Example Sketch
Authors:  Nathan D. Holmes <maverick@drgw.net>
File:     $Id: $
License:  GNU General Public License v3

LICENSE:
    Copyright (C) 2014 Nathan D. Holmes & Michael D. Petersen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

*************************************************************************/

/*
  This sketch will demonstrate how to use the Ard2499 library for the 
  Iowa Scaled Engineering ARD-LTC2499 shield.   For more information about the
  ARD-LTC2499, see here:  http://www.iascaled.com/store/ARD-LTC2499
  
  The jumpers for ADC address and EEPROM address should be left open, or the 
  defines for the ADC and EEPROM addresses should be changed in the setup() function.
*/

#include <Wire.h>
#include <Ard2499.h>

Ard2499 ard2499board1;

byte confChan=0; 

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Wire1.begin();
  ard2499board1.begin(ARD2499_ADC_ADDR_ZZZ, ARD2499_EEP_ADDR_ZZ);
  ard2499board1.ltc2499ChangeConfiguration(LTC2499_CONFIG2_60_50HZ_REJ);
  ard2499board1.ltc2499ChangeChannel(LTC2499_CHAN_SINGLE_0P);

}
byte i=0;

void loop() {

  for(i=0; i<17; i++)
  {
    byte newChannel;
    
    switch(i)
    {
       case 0:
          newChannel = LTC2499_CHAN_SINGLE_1P;
          break;
          
       case 1:
          newChannel = LTC2499_CHAN_SINGLE_2P;
          break;

       case 2:
          newChannel = LTC2499_CHAN_SINGLE_3P;
          break;

       case 3:
          newChannel = LTC2499_CHAN_SINGLE_4P;
          break;

       case 4:
          newChannel = LTC2499_CHAN_SINGLE_5P;
          break;
          
       case 5:
          newChannel = LTC2499_CHAN_SINGLE_6P;
          break;

       case 6:
          newChannel = LTC2499_CHAN_SINGLE_7P;
          break;

       case 7:
          newChannel = LTC2499_CHAN_SINGLE_8P;
          break;

       case 8:
          newChannel = LTC2499_CHAN_SINGLE_9P;
          break;
          
       case 9:
          newChannel = LTC2499_CHAN_SINGLE_10P;
          break;

       case 10:
          newChannel = LTC2499_CHAN_SINGLE_11P;
          break;

       case 11:
          newChannel = LTC2499_CHAN_SINGLE_12P;
          break;

       case 12:
          newChannel = LTC2499_CHAN_SINGLE_13P;
          break;

       case 13:
          newChannel = LTC2499_CHAN_SINGLE_14P;
          break;

       case 14:
          newChannel = LTC2499_CHAN_SINGLE_15P;
          break;

       case 15:
          newChannel = LTC2499_CHAN_TEMPERATURE;
          break;

       case 16:
       default:
          newChannel = LTC2499_CHAN_SINGLE_0P;
          break;

    }

    if (i != 16)
    { 
      Serial.print(String("Channel "));
      Serial.print(String(i+1));
      Serial.print(String(" SE"));
      Serial.print(String(" = ["));
      Serial.print(String(float((ard2499board1.ltc2499ReadAndChangeChannel(newChannel)*2.048)/16777216.0),6));
      Serial.print("]\n");
    }
  }
  
  delay(1000);
}
