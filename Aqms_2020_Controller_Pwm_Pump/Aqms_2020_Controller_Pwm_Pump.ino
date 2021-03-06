int in = 0; 
void setup() {
    Serial.begin(9600);
    pinMode(5, OUTPUT); //PWM Pump 1
    pinMode(6, OUTPUT); //PWM Pump 2
    Serial.println("Ready");
}

void loop() {
    if (Serial.available() > 0) {
        in = Serial.parseInt();
        if(in > 0){
            if(in == 1) in = 0;
            if(in <= 100){
                analogWrite(6,0);
                in = map(in, 0, 100, 0, 255);
                for (int i = 0; i <= in; i+=1) {
                    analogWrite(5,i);
                    delay(15);
                }
            } else {
                analogWrite(5,0);
                in = map(in, 101, 200, 0, 255);
                for (int i = 0; i <= in; i+=1) {
                    analogWrite(6,i);
                    delay(15);
                }
            }
        }
    }
}
