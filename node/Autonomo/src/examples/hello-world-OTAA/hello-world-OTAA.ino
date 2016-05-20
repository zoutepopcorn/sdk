#include "TheThingsUno.h"

//#define SerialUSB Serial
#define loraSerial Serial1

TheThingsUno ttu;

void setup()
{
  SerialUSB.begin(115200);
  loraSerial.begin(57600);

  while (SerialUSB) {
    ;
  }

  //lora power pin
  pinMode(BEE_VCC, OUTPUT);
  // Turn the LoRaBee on
  digitalWrite(BEE_VCC, HIGH);

  delay(1000);
  ttu.init(loraSerial, SerialUSB);  //Initializing...
  delay(1000);
}

void loop()
{
  SerialUSB.println("Device Information");
  SerialUSB.println();
  ttu.showStatus();
  SerialUSB.println();
  SerialUSB.println("use the device `EUI` to register the device for OTAA \n");
  SerialUSB.println("--------------------------------------------------------------");
  SerialUSB.println();
  delay(10000);
}
