/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: Alkoholtester mit MQ-03 Sensor und 128 x 64 Pixel LCD Display 12864 Display Modul
!!!Bei den Gas-Sensoren ist zu beachten das diese sehr viel Strom benötigen, sowie eine gewisse Vorheiztzeit benötigen!!!
A254
**************************************************************************************************
Version: 14.07.2024
**************************************************************************************************
Board: NANO
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries
C:\Users\User\Documents\Arduino
D:\gittemp\Arduino II\A156_Wetterdaten_V3
**************************************************************************************************
C++ Arduino IDE V1.8.19
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json

Verdrahtung:

Nano V3   MQ-03   Display   
GND       GND     GND 
5V        VCC     VCC 
A0        A0      NC
D3                RS  
D4                R/W 
D5                E 
D6                RST 
3.3V              BLA 
BLK               GND
**************************************************************************************************/
#include "U8glib.h"

U8GLIB_ST7920_128X64_1X u8g(5, 4, 3 , 6);

#define qtdLED 6

int LEDs[qtdLED];
int count;
int value_sensor = 0;
unsigned long time;
int maxTime = 300;
int status = 1;
String state;
int position1;
int i;
int j;
int maximumReading;

void draw() {
  u8g.setFont(u8g_font_8x13B);
  u8g.drawRFrame(0, 20, 128, 44, 4);
  u8g.drawStr( 30, 10, "AlcoTester");
  u8g.setFont(u8g_font_robot_de_niro);
  u8g.drawStr( 8, 20, "Don't drink and drive");
  u8g.setFont(u8g_font_8x13B);
  u8g.drawStr( 10, 37, "Wait");
  if (status == 1) {
    u8g.drawBox(80, 25, 20, 30);
    u8g.drawHLine(77, 24, 26);
    u8g.drawRFrame(78, 25 , 24, 32, 0);
    u8g.drawRFrame(77, 25 , 26, 32, 0);
    u8g.drawHLine(76, 57, 28);
    u8g.drawHLine(76, 58, 28);
    u8g.drawRFrame(102, 30 , 7, 20, 2);
    u8g.drawRFrame(102, 28 , 9, 24, 2);
    u8g.setColorIndex(0);
    if (time == 0) {
      time = 1;
    }
    u8g.drawBox(79, 25, 22, time);
    u8g.setColorIndex(1);
  }
  if (status == 0) {
    u8g.setFont(u8g_font_fub20);
    u8g.setColorIndex(0);
    u8g.drawBox(10, 25, 110, 33);
    u8g.setColorIndex(1);
    if (value_sensor <= 99) {
      position1 = 50;
    }
    else {
      position1 = 43;
    }
    u8g.setPrintPos(position1, 45);
    u8g.print(value_sensor);
    u8g.setFont(u8g_font_orgv01);
    int size = state.length();
    int position = (128 / 2) - ((size * 5) / 2);
    u8g.setPrintPos(position, 60);
    u8g.print(state);
  }
}

void setup(void) {
  
  Serial.begin(115000);
  pinMode(A0, INPUT);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
  i = 0;
  j = 7;
  while (i < qtdLED) {
    LEDs[i] = j;
    i++;
    j++;
  }
  for (i = 0; i < qtdLED; i++)
  {
    pinMode(LEDs[i], OUTPUT);
  }
  digitalWrite(2, OUTPUT);
}

void loop(void) {
  
  value_sensor = analogRead(A0);
  time = millis() / 1000;
  u8g.firstPage();
  if (time <= maxTime) {
    time = map(time, 0, maxTime, 0, 30);
    status = 1;
  }
  else {
    status = 0;
  }
  if (value_sensor >= 0 and value_sensor <= 100) {
    state = "kein Bier?";
  }
  else if (value_sensor >= 101 and value_sensor <= 200) {
    state = "war wohl nur Apfelsaft";
  }
  else if (value_sensor >= 201 and value_sensor <= 300) {
    state = "Sicher das es nur ein Bier war?";
  }
  else if (value_sensor >= 301 and value_sensor <= 400) {
    state = "Da war wohl Schnaps dabei!";
  }
  else if (value_sensor >= 401 and value_sensor <= 550) {
    state = "Sogar in Bayern zuviel!";
  }
  else if (value_sensor >= 551) {
    state = "Ähm... Krankenwagen?";
  }
  do {
    draw();
  }
  while (u8g.nextPage() );
  delay(50);
  
  
  int sensor = analogRead(A0);
  if (sensor >= 40) {
    digitalWrite(2, HIGH);
    maximumReading = 0;
    for (count = 0; count <= 500; count++) {
      int sensor = analogRead(A0);
      delay(1);
      if (sensor > maximumReading) {
        maximumReading = sensor;
      }
    }
    digitalWrite(2, LOW);
    int level = map(maximumReading, 0, 551, 0, qtdLED);
    for (i = 0; i < qtdLED; i++) {
      if (i < level) {
        digitalWrite(LEDs[i], HIGH);
        delay(100);
      } else {
        digitalWrite(LEDs[i], LOW);
      }
    }
    delay(500);
    for (i = 0; i < qtdLED; i++) {
      digitalWrite(LEDs[i], LOW);
    }
  }
}
