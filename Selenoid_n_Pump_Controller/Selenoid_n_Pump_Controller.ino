
int span_cs2 = 9;
int span_h2s = 10;
int zero = 11;
int sample = 4;
int purge = 5;
int pump = 6;

char inChar;
void setup() {
    Serial.begin(9600);
    pinMode(pump, OUTPUT);
    pinMode(sample, OUTPUT);
    pinMode(zero, OUTPUT);
    pinMode(span_h2s, OUTPUT);
    pinMode(span_cs2, OUTPUT);
    pinMode(purge, OUTPUT);
    digitalWrite(pump,HIGH);
    digitalWrite(sample,HIGH);
    digitalWrite(zero,HIGH);
    digitalWrite(span_h2s,HIGH);
    digitalWrite(span_cs2,HIGH);
    digitalWrite(purge,HIGH);
}

void loop() {
    if (Serial.available() > 0) {
        inChar = Serial.read();
        if(inChar == 'i'){
            digitalWrite(pump,HIGH);
        }
        if(inChar == 'j'){
            digitalWrite(pump,LOW);
        }

        if(inChar == 'q'){//sample
            digitalWrite(sample,HIGH);
            digitalWrite(zero,HIGH);
            digitalWrite(span_h2s,HIGH);
            digitalWrite(span_cs2,HIGH);
        }
        if(inChar == 'w'){//zero
            digitalWrite(sample,LOW);
            digitalWrite(zero,LOW);
            digitalWrite(span_h2s,HIGH);
            digitalWrite(span_cs2,HIGH);
        }
        if(inChar == 'e'){//span_h2s
            digitalWrite(sample,LOW);
            digitalWrite(zero,HIGH);
            digitalWrite(span_h2s,LOW);
            digitalWrite(span_cs2,HIGH);
        }
        if(inChar == 'r'){//span_cs2
            digitalWrite(sample,LOW);
            digitalWrite(zero,HIGH);
            digitalWrite(span_h2s,HIGH);
            digitalWrite(span_cs2,LOW);
        }

        
        if(inChar == 'o'){
            digitalWrite(purge,HIGH);
        }
        if(inChar == 'p'){
            digitalWrite(purge,LOW);
        }
    }
}
