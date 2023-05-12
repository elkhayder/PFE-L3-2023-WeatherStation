#ifndef _CUSTOM_STORAGE_H
#define _CUSTOM_STORAGE_H

#include <SPI.h>
#include <SdFat.h>
#include <ArduinoJson.h>

#include "WiFi.h"
#include "Clock.h"

#define SD_CS_PIN 7

namespace Custom::Storage
{
    typedef struct FileDescription
    {
        String path;
        size_t size;
    } FileDescription;

    extern SdFat sd;

    void setup();
}

#endif