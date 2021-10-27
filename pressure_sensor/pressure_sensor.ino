int sensor1 = A0;
int sensor2 = A1;
int val1 = 0;
int val2 = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val1 = analogRead(sensor1);
  val2 = analogRead(sensor2);
  Serial.print(val1);
  Serial.print(":");
  Serial.println(val2);
  delay(1000);
}
