int pump = 9;
int sample = 10;
int zero = 11;
int span_h2s = 4;
int span_cs2 = 5;
int purge = 6;

char inChar;
void setup() {
    Serial.begin(9600);
    pinMode(pump, OUTPUT);
    pinMode(sample, OUTPUT);
    pinMode(zero, OUTPUT);
    pinMode(span_h2s, OUTPUT);
    pinMode(span_cs2, OUTPUT);
    pinMode(purge, OUTPUT);
    digitalWrite(pump,LOW);
    digitalWrite(sample,HIGH);
    digitalWrite(zero,LOW);
    digitalWrite(span_h2s,LOW);
    digitalWrite(span_cs2,LOW);
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
            digitalWrite(zero,LOW);
            digitalWrite(span_h2s,LOW);
            digitalWrite(span_cs2,LOW);
        }
        if(inChar == 'w'){//zero
            digitalWrite(sample,LOW);
            digitalWrite(zero,HIGH);
            digitalWrite(span_h2s,LOW);
            digitalWrite(span_cs2,LOW);
        }
        if(inChar == 'e'){//span_h2s
            digitalWrite(sample,LOW);
            digitalWrite(zero,LOW);
            digitalWrite(span_h2s,HIGH);
            digitalWrite(span_cs2,LOW);
        }
        if(inChar == 'r'){//span_cs2
            digitalWrite(sample,LOW);
            digitalWrite(zero,LOW);
            digitalWrite(span_h2s,LOW);
            digitalWrite(span_cs2,HIGH);
        }
    }
}
