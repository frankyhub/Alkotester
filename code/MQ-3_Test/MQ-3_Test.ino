/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: MQ-3 Test mit Library <MQ3.h>

**************************************************************************************************
Version: 16.07.2024
**************************************************************************************************
Board: NANO
**************************************************************************************************
Libraries:
#include <MQ3.h>

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
#include <MQ3.h>

#define MQ_PIN A0

MQ3 mq(MQ_PIN, false, 1000); // Here I use sensor have logic 3.3v (isPower5v=false) and R2=1kOhm (default 2kOhm)

void setup()
{
  Serial.begin(9600);
  Serial.print(F("MQ3 Test!\n"));
  Serial.print(F("Bitte warten, bis sich die Sensorsonde erwärmt hat (~20s)"));
  mq.begin();
  Serial.print(F("Fertig\n"));
}

void loop()
{
  float alcohol = mq.readRawValueOfAlcohol(); // Unit (mg/L) of (BrAC)
  Serial.print(F("Alcohol-Level: "));
  Serial.print(alcohol, 2); Serial.print(F(" mg/L ; "));
  Serial.print(mq.convertRawToPPM(alcohol), 0); Serial.print(F("ppm ; "));
  Serial.print(mq.convertRawToBAC(alcohol), 2); Serial.print(F("% BAC ; "));
  Serial.print(mq.convertRawToGramPerMillilitre(alcohol), 4); Serial.print(F(" g/mL\n"));

  delay(1000);
}
