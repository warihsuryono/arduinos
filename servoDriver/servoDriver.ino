#include <Servo.h>
Servo servo1;
byte val;



void setup()
{
  servo1.attach(9); 
  Serial.begin(9600); 
}

void loop()
{
  Serial.println("0");
  servo1.write(0); 
  delay(500);
  Serial.println("45");
  servo1.write(45); 
  delay(500);
  Serial.println("90");
  servo1.write(90); 
  delay(500);
  Serial.println("135");
  servo1.write(135); 
  delay(500);
  Serial.println("180");
  servo1.write(180); 
  delay(500);
  Serial.println("135");
  servo1.write(135); 
  delay(500);
  Serial.println("90");
  servo1.write(90); 
  delay(500);
  Serial.println("45");
  servo1.write(45); 
  delay(500);
}
