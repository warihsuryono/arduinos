//int pin8  = 8;
int sensor = A1;
int sensorValue = 0;

const float r1 = 47000.0;

void setup() {
  // put your setup code here, to run once:
 // pinMode [pin8, OUTPUT];
  Serial.begin(9600);
}

void loop() {
  /*sensorValue = analogRead(sensor);
  Serial.println(sensorValue,DEC);
  if (sensorValue > 500) {
    digitalWrite(pin8, HIGH);
  }
  else {
    digitalWrite(pin8,LOW);
  }*/

  sensorValue = analogRead(sensor);
  /*float rs = r1 * ((1023.0 / sensorValue) - 1.0);
  const float ro = sensorValue*3.4;
  int ppm = rs/ro;*/

  float rs = r1 * ((1023.0 / sensorValue) - 1.0);
// float rs = r1 * (1.0-9 (1023.0 / sensorValue));
   float ro = rs/r1;
  //float lgppm = (log10(ro)* (-2.6)+ 2.7);
  //float ppm =(10/7)* pow(10,lgppm);
  //double pwr=
   float ppm =(5 - 0.6151*pow(ro,-1.903));
//    if (ppm >= 0) { 
//      ppm=ppm;}
//    else {
//      ppm=0;}
  float ppmA=1.2913*(25*(ppm)-84);
  if (ppmA >= 0) { 
      ppmA=ppmA;}
    else {
      ppmA=0;}
  Serial.print("resistansi sensor : ");
 // Serial.print(sensorValue,DEC);
  Serial.println(  ro,DEC);
  Serial.print("nilai ppm :");
  Serial.println(ppmA);
  //Serial.println (1.2913*(200*(ppm)-84));
  delay(1000);
  

}
