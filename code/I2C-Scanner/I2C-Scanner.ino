/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: NANO I2C-Scanner
 * scannt den I2C-Bus und gibt die Anzahl der Busteilnehmer
 * und die Adressen auf den Seriellen Monitor aus
**************************************************************************************************
Version: 15.07.2024
**************************************************************************************************
Board: NANO
*  SCL an A4 SDA an A5
*  Adressen:
*  OLED-Disolay: 0X3C
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries
C:\Users\User\Documents\Arduino
D:\gittemp\Arduino II\A156_Wetterdaten_V3
**************************************************************************************************
C++ Arduino IDE V1.8.19

R2-D2
2QK384JVPX
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
**************************************************************************************************/

#include <Wire.h>

byte errorResult;           // error code returned by I2C Wire.endTransmission()
byte i2c_addr;              // I2C address being pinged
byte lowerAddress = 0x08;   // I2C lowest valid address in range
byte upperAddress = 0x77;   // I2C highest valid address in range
byte numDevices;            // how many devices were located on I2C bus

void setup() {
  Wire.begin();             // I2C init
  Serial.begin(9600);       // search results show up in serial monitor
}

void loop() {
  Serial.print("Scanning I2C 7-bit address range 0x");
  if (lowerAddress < 0x10)                                // pad single digit addresses with a leading "0"
    Serial.print("0");
  Serial.print(lowerAddress, HEX);
  Serial.print(" to 0x");
  Serial.print(upperAddress, HEX);
  Serial.println(".");

  numDevices = 0;

  for (i2c_addr = lowerAddress; i2c_addr <= upperAddress; i2c_addr++ )     // loop through all valid I2C addresses
  {
    Wire.beginTransmission(i2c_addr);                     // initiate communication at current address
    errorResult = Wire.endTransmission();                 // if a device is present, it will send an ack and "0" will be returned from function

    if (errorResult == 0)                                 // "0" means a device at current address has acknowledged the serial communication
    {
      Serial.print("I2C device found at address 0x");

      if (i2c_addr < 0x10)                                // pad single digit addresses with a leading "0"
        Serial.print("0");

      Serial.println(i2c_addr, HEX);                      // display the address on the serial monitor when a device is found
      numDevices++;
    }
  }

  Serial.print("Scan complete.  Devices found: ");
  Serial.println(numDevices);
  Serial.println();

  delay(10000);                                           // wait 10 seconds and scan again to detect on-the-fly bus changes
}
