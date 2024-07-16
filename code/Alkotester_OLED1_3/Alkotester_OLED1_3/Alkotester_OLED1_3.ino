/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
  Funktion: Alktester mit einem NANO und einem OLED-Display 1,3"

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
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
int TIME_UNTIL_WARMUP = 300;
unsigned long time;


int analogPin = 0;
int val = 0;


void setup()   {

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.display();
}


void loop() {

  delay(100);

  val = readAlcohol();
  printTitle();
  printWarming();

  time = millis() / 1000;

  if (time <= TIME_UNTIL_WARMUP)
  {
    time = map(time, 0, TIME_UNTIL_WARMUP, 0, 100);
    display.drawRect(10, 50, 110, 10, WHITE); //Empty Bar
    display.fillRect(10, 50, time, 10, WHITE);
  } else
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
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(5, 0);
  display.println("Alkotester");

}

void printWarming()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 30);
  display.println("Sensor aufwaermen");
}

void printAlcohol(int value)
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45, 25);
  display.println(val);
}

void printAlcoholLevel(int value)
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 45);

  if (value < 200)
  {
    display.println("1 Radler");
  }
  if (value >= 200 && value < 280)
  {
    display.println("2 Hoibe");
  }
  if (value >= 280 && value < 350)
  {
    display.println("5 Hoibe");
  }
  if (value >= 350 && value < 450)
  {
    display.println("5 Mass");
  }

  if (value >= 450 && value < 550)
  {
    display.println("8 Mass");
  }

  if (value >= 550 && value < 750)
  {
    display.println("Hinlegen!");
  }

  if (value > 750)
  {
    display.println("Notarzt!");
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

  val = (val1 + val2 + val3) / 3;
  return val;
}
