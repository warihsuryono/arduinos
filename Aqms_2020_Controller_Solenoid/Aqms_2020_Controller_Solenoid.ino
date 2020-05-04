void setup() {
  pinMode(2, OUTPUT); //Sample Inlet
  pinMode(3, OUTPUT); //Zero Inlet
  pinMode(4, OUTPUT); //Span Inlet
  pinMode(5, OUTPUT); //By Pass
  pinMode(6, OUTPUT); //Cal. ByPass
  Serial.begin(9600);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'i') {//sampling
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
    }
    if (c == 'j') {//zero
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    }
    if (c == 'k') {//span
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
    }
  }
}
