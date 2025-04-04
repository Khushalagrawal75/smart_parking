# Smart Parking System 🚗

An **Online service** that simplifies **vehicle parking** and real time parking management. 

## 🌐 Overview 

This provides real time parking monitoring through mobile app *Blynk* which will show the blank slots for parking and the parked slot using IoT devices like `Arduino` and `Nodemcu ESP8266`.
Language used is `c++`.

## 🛠️ Components Needed

|  Component  | Quantity  |
|-------------|-----------|
| 📼 Arduino  | 1 |
| 🛜 Nodemcu ESP8266 | 1 |
| ⌨️ BreadBoard | 1 |
| 🔋 9V Battery | 2 |
| 🕹️ IR Sensor | 3 |
| 🪢 Jumper Wires | - |

## ⚡ Circuit  

1. **Installation**
    - Install Arduino IDE [Here](https://www.arduino.cc/en/software)
    - Download the libraries [Blynk](https://github.com/blynkkk/blynk-library/releases/download/v1.3.2/Blynk_Release_v1.3.2.zip)
    - Download the ESP8266 library in Arduino IDE.
    - Open Arduino IDE > File > Preferences > paste the link in Additional Board manager url http://arduino.esp8266.com/stable/package_esp8266com_index.json
    - Download *Blynk* app in mobile and Sign Up.

2. **Coding**
    - Compile and Upload the codes in Arduino - [Here](./Arduino.ino)
    - Compile and Upload the codes in Nodemcu - [Here](ESP.ino)

3. **Arduino Connections**
    - Connect Arduino `4th` , `5th` and `6th` pin to `OUT` pin in IR sensor 1, 2 and 3 respectively.
    - Connect the Arduino `5V` pin to the Breadboard and then to `VCC` pin in IR sensor 1, 2 and 3 respectively.
    - Connect the Arduino `GND` pin to the Breadboard and then to `GND` pin in IR sensor 1, 2 and 3 respectively.
    - Connect `+ve` of 9V battery to Arduino `Vin` and `-ve` to Arduino `GND`.

4. **Nodemcu Connections**
    - Connect the Nodemcu `RX` and `TX` to `3rd` and `2nd` pin of Arduino.
    - Connect `+ve` of 9V battery to Nodemcu `Vin` and `-ve` to Arduino `GND`.

5. ***Blynk* app Connections**
    - Create a Dashboards > Create Dashboard.
    - In this dashboard add 3 leds and place each led as per your convenience.
    - Select virtual pins as V10, V11, V12.
    - Go to Devices > Add new device > Template > Choose the newly Created Dashboard.
    - On the Top right corner we have our authentication id of blynk.

## 📷 Images

- Circuit Diagram: [Image](./CircuitDiagram.jpg)
- Demonstration: [Image](./Demonstration.jpg)
- Labelled Diagram: [Image](./Labelled_IMG.jpg)

## </> Coding 
### -> This is for Arduino
```C++
//For Arduino
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
```
### -> This is for Nodemcu ESP8266
```c++
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char auth[] = "authentication id of blynk";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Your WiFi name";
char pass[] = "Your WiFi pass";

BlynkTimer timer;

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

int firstVal, secondVal,thirdVal; // sensors
int led1,led2,led3;
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
// You can send any value at any time.
// Please don't send more that 10 values per second.
Blynk.virtualWrite(V1, millis() / 1000);
}

void setup()
{
// Debug console
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);

timer.setInterval(1000L,sensorvalue1);
timer.setInterval(1000L,sensorvalue2);
timer.setInterval(1000L,sensorvalue3);
}

void loop()
{
if (Serial.available() == 0 )
{
Blynk.run();
timer.run(); // Initiates BlynkTimer
}

if (Serial.available() > 0 )
{
rdata = Serial.read();
myString = myString+ rdata;
// Serial.print(rdata);
if( rdata == '\n')
{
Serial.println(myString);
// Serial.println("fahad");
// new code
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2);

// these leds represents the leds used in Blynk application
led1 = l.toInt();
led2 = m.toInt();
led3 = n.toInt();

myString = "";
// end new code
}
}
}

void sensorvalue1()
{
int sdata = led1;
// You can send any value at any time.
// Please don't send more that 10 values per second.
Blynk.virtualWrite(V10, sdata);
}

void sensorvalue2()
{
int sdata = led2;
// You can send any value at any time.
// Please don't send more that 10 values per second.
Blynk.virtualWrite(V11, sdata);
}

void sensorvalue3()
{
int sdata = led3;
// You can send any value at any time.
// Please don't send more that 10 values per second.
Blynk.virtualWrite(V12, sdata);
}

String getValue(String data, char separator, int index)
{
int found = 0;
int strIndex[] = { 0, -1 };
int maxIndex = data.length() - 1;

for (int i = 0; i <= maxIndex && found <= index; i++) {
if (data.charAt(i) == separator || i == maxIndex) {
found++;
strIndex[0] = strIndex[1] + 1;
strIndex[1] = (i == maxIndex) ? i+1 : i;
}
}
return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
```



