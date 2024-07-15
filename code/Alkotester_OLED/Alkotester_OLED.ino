/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: Alktester mit einem NANO und einem OLED-Display 0,96"

**************************************************************************************************
Version: 15.07.2024
**************************************************************************************************
Board: NANO V3
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
**************************************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
int TIME_UNTIL_WARMUP = 900;
unsigned long time;


int analogPin = 0;
int val = 0;
Adafruit_SSD1306 display(OLED_RESET);


void setup()   {                

 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.clearDisplay();
}


void loop() {  
  
  delay(100);

  val = readAlcohol();
  printTitle();
  printWarming();

  time = millis()/1000;
  
  if(time<=TIME_UNTIL_WARMUP)
  {
    time = map(time, 0, TIME_UNTIL_WARMUP, 0, 100);
    display.drawRect(10, 50, 110, 10, WHITE); //Empty Bar
    display.fillRect(10, 50, time,10,WHITE);
  }else
  {
     printTitle();
     printAlcohol(val);
     printAlcoholLevel(val);  
  }
  display.display();

}


void printTitle()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22,0);
  display.println("Alkotester");
}

void printWarming()
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("Aufw\xE4rmen");
}

void printAlcohol(int value)
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45,25);
  display.println(val);
}

void printAlcoholLevel(int value)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,55);
  
  if(value<200)
  {
      display.println("war wohl nur Apfelsaft?");
  }
  if (value>=200 && value<280)
  {
      display.println("Sicher das es nur ein Bier war?");
  }
  if (value>=280 && value<350)
  {
      display.println("Da war wohl Schnaps dabei!");
  }
  if (value>=350 && value <450)
  {
      display.println("Sogar in Bayern zuviel!");
  }
  if(value>450)
  {
     display.println("Ähm... Krankenwagen?");
  }
 }
 
 int readAlcohol()
 {
  int val = 0;
  int val1;
  int val2;
  int val3; 


  display.clearDisplay();
  val1 = analogRead(analogPin); 
  delay(10);
  val2 = analogRead(analogPin); 
  delay(10);
  val3 = analogRead(analogPin);
  
  val = (val1+val2+val3)/3;
  return val;
 }
