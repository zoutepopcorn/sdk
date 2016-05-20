#include "TheThingsUno.h"

#define debugSerial Serial
#define loraSerial Serial1

TheThingsUno ttu;

void setup()
{
  debugSerial.begin(115200);
  loraSerial.begin(57600);

  delay(1000);

  ttu.init(loraSerial, debugSerial);  //Initializing...
  SerialUSB.println("Setup for The Things Network complete");

  delay(1000);
}

void loop()
{
    debugSerial.println();
    debugSerial.println("--------------------------------------------------------------");
    debugSerial.println("Device Information");
    debugSerial.println();
    ttu.showStatus();
    debugSerial.println();
    debugSerial.println("use the device `EUI` to register the device for OTAA \n");

    delay(10000);
}
