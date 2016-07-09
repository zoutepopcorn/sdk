# The Things Uno SDK

## Introduction

This is the Arduino library for The Things Uno to communicate with The Things Network. You can also use this library for other Arduino-compatible devices featuring the Microchip RN2xx3 chip.

## Installation

1. Download the latest zip file from the `release` folder
2. In the Arduino IDE, go to Sketch -> Include Library -> Add .ZIP Library
3. Select `TheThingsUno.zip`
4. Verify that the Board under Tools is set to Arduino Leonardo and Port is set to the device connected to your pc

## Example using ABP (activation by personalization)

Open the `hello-world` example from File -> Examples -> TheThingsUno, or paste the following code in a new sketch:

```Arduino
#include "TheThingsUno.h"

// Set your AppEUI and AppKey
const byte appEui[8] = {0x70, 0xB3, 0xD5, 0x7E, 0xE0, 0xE0, 0x01, 0x4A1};
const byte appKey[16] = {0x73, 0x6D, 0x24, 0xD2, 0x69, 0xBE, 0xE3, 0xAE, 0x0E, 0xCE, 0xF0, 0xBB, 0x6C, 0xA4, 0xBA, 0xFE};

#define debugSerial Serial
#define loraSerial Serial1

#define debugPrintLn(...) { if (debugSerial) debugSerial.println(__VA_ARGS__); }
#define debugPrint(...) { if (debugSerial) debugSerial.print(__VA_ARGS__); }

TheThingsUno ttu;

void setup()
{
  debugSerial.begin(115200);
  loraSerial.begin(57600);

  delay(1000);
  ttu.init(loraSerial, debugSerial);
  ttu.reset();
  ttu.join(appEui, appKey);

  delay(6000);
  ttu.showStatus();
  debugPrintLn("Setup for The Things Network complete");

  delay(1000);
}

void loop() {
  ttu.sendString("Hello world!");

  delay(20000);
}
```

Click Verify to compile the sketch. Click Upload to upload the example to your The Things Uno.

## API

TheThingsUno class features the following public methods:

```C++
  public:
    int downlinkPort;
    byte downlink[64];
    void init(Stream& modemStream, Stream& debugStream);
    void reset(bool adr = true, int sf = DEFAULT_SF, int fsb = DEFAULT_FSB);
    bool personalize(const byte devAddr[4], const byte nwkSKey[16], const byte appSKey[16]);
    bool join(const byte appEui[8], const byte appKey[16]);
    int sendBytes(const byte* buffer, int length, int port = 1, bool confirm = false);
    int sendString(String message, int port = 1, bool confirm = false);
    void showStatus();
```
