int status = 0;
void setup() {
  pinMode(22, OUTPUT);
}

void loop() {
	if(status == 1){
		digitalWrite(22, HIGH);
		status = 0;
	} else {
		digitalWrite(22, LOW);
		status = 1;
	}
	delay(120 * 60000);
}
