bool juststart;
String read_string = "";

void setup() {
    Serial.begin(115200);
    juststart = true;
    read_string = "";
}

void loop() {
    if(juststart){
      Serial.println("ready");
      read_string = Serial.readStringUntil('\n');
      if(read_string.equals("start")){
        juststart = false;
      }
    } else {
      float cc = random(2700,3500)/100;
      float dd = random(5000,8000)/100;
      float ff = random(2700,3500)/100;
      float gg = random(5000,8000)/100;
      Serial.println("H,0,8,in," + String(cc) + "," + String(dd) + ",0,out," + String(ff) + "," + String(gg) + ",0,T");
    }
    delay(1000);
}
