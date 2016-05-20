#include "TheThingsUno.h"

// Set your device address
const byte devAddr[4] = {0x02, 0xDE, 0xAE, 0x00};

// Set your NwkSKey and AppSKey
const byte nwkSKey[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
const byte appSKey[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};

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
  ttu.personalize(devAddr, nwkSKey, appSKey);

  delay(6000);
  ttu.showStatus();
  SerialUSB.println("Setup for The Things Network complete");

  delay(1000);
}

void loop() {
  ttu.sendString("Hello world!");

  delay(5000);
}
