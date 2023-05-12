#ifndef _CUSTOM_LORA_H
#define _CUSTOM_LORA_H

#include <RH_RF95.h>
#include <ArduinoJson.h>

#include "Storage.h"

#define FREQUENCY 864.0

namespace Custom::Lora
{
    extern RH_RF95<HardwareSerial> rf95;
    extern String buffer;

    void setup();
    void loop();
    void parsePayload();
}

#endif