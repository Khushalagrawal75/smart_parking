#include <SoftwareSerial.h>

SoftwareSerial nodemcu(2,3);

int parkingslot1_ir_s = 4; // parking slot1 infrared sensor connected with pin number 4 of arduino
int parkingslot2_ir_s = 5;
int parkingslot3_ir_s = 6;

String sensor1;
String sensor2;
String sensor3;

String cdata =""; // complete data, consisting of sensors values

void setup()
{
Serial.begin(9600);
nodemcu.begin(9600);

pinMode(parkingslot1_ir_s, INPUT);
pinMode(parkingslot2_ir_s, INPUT);
pinMode(parkingslot3_ir_s, INPUT);
}

void loop()
{
p1slot1();
p1slot2();
p1slot3();

cdata = cdata + sensor1 +"," + sensor2 + ","+ sensor3; // comma will be used a delimeter
Serial.println(cdata);
nodemcu.println(cdata);
delay(6000); // 100 milli seconds
cdata = "";
digitalWrite(parkingslot1_ir_s, HIGH);
digitalWrite(parkingslot2_ir_s, HIGH);
digitalWrite(parkingslot3_ir_s, HIGH);
}

void p1slot1() // parkng slot1
{
if( digitalRead(parkingslot1_ir_s) == LOW)
{
sensor1 = "255";
delay(200);
}
if( digitalRead(parkingslot1_ir_s) == HIGH)
{
sensor1 = "0";
delay(200);
}
}

void p1slot2() // parking slot2
{
if( digitalRead(parkingslot2_ir_s) == LOW)
{
sensor2 = "255";
delay(200);
}
if( digitalRead(parkingslot2_ir_s) == HIGH)
{
sensor2 = "0";
delay(200);
}
}

void p1slot3() // parking slot3
{
if( digitalRead(parkingslot3_ir_s) == LOW)
{
sensor3 = "255";
delay(200);
}
if( digitalRead(parkingslot3_ir_s) == HIGH)
{
sensor3 = "0";
delay(200);
}
}