#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial_Black_16.h>
const int WIDTH = 9;

SoftDMD dmd(WIDTH,1);
//DMD_TextBox box1(dmd,0,0,96,0);//L,T,W,H
DMD_TextBox box2(dmd,192,0,96,0);
//char *MESSAGE1 = "Text Atas     ";
//char *MESSAGE2 = "Text Bawah    ";
void setup() {
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
	dmd.setBrightness(6);
	dmd.selectFont(Arial_Black_16);
	dmd.begin();
  //box1.print("Text Atas");
  box2.print("Text Baw");
}
void loop() {
	//const char *msg1 = MESSAGE1;
	//const char *msg2 = MESSAGE2;
	//dmd.drawFilledBox(32,15,34,10);//x1,y1,x2,y2
	//dmd.drawFilledBox(36,15,38,8);
	//dmd.drawFilledBox(40,15,42,2);
	//while(*msg1 || *msg2) {
	//	box1.print(*msg1);
	//	box2.print(*msg2);
	//	delay(50);
	//	msg1++;
	//	msg2++;
	//}
}
