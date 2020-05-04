void setup() {
  pinMode(2, OUTPUT); //PSU PUMP1
  pinMode(3, OUTPUT); //PSU PUMP2
  pinMode(4, OUTPUT); //PSU SENSOR
  pinMode(5, OUTPUT); //FAN
  pinMode(6, OUTPUT); //PSU Peltier Cooler
  pinMode(7, OUTPUT); //PSU PM
  //Serial.begin(9600);
  digitalWrite(5, HIGH);
  delay(10000);
  digitalWrite(6, HIGH);
  delay(10000);
  digitalWrite(7, HIGH);
  delay(10000);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  delay(10000);
  digitalWrite(4, HIGH);
}

void loop() {
//  if (Serial.available() > 0) {
//    char c = Serial.read();
//    if (c == 'i') {
//      digitalWrite(2, HIGH);
//      digitalWrite(3, LOW);
//    }
//    if (c == 'j') {
//      digitalWrite(2, LOW);
//      digitalWrite(3, HIGH);
//    }
//  }
}
