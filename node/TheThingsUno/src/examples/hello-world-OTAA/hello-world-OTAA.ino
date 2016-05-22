#include "TheThingsUno.h"

// Set your app Credentials
const byte appEui[8] = {0x70, 0xB3, 0xD5, 0x7E, 0xE0, 0xE0, 0x01, 0x4A};
const byte appKey[16] = {0x73, 0x6D, 0x24, 0xD2, 0x69, 0xBE, 0xE3, 0xAE, 0x0E, 0xCE, 0xF0, 0xBB, 0x6C, 0xA4, 0xBA, 0xFE};

#define loraSerial Serial1

TheThingsUno ttu;

void setup()
{
  SerialUSB.begin(115200);
  loraSerial.begin(57600);

  while (SerialUSB) {
    ;
  }

  delay(1000);
  ttu.init(loraSerial, SerialUSB); //Initializing...
  ttu.reset();
  ttu.join(appEui, appSKey);

  delay(6000);
  ttu.showStatus();
  SerialUSB.println("Setup for The Things Network complete");

  delay(1000);
}

void loop() {
  ttu.sendString("Hello world!");

  delay(20000);
}
