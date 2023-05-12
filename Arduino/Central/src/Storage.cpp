#include "Storage.h"
#include "helpers.h"

namespace Custom::Storage
{
    SdFat sd;
    File db;

    void setup()
    {

        // SD
        if (!sd.begin(SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(50))))
        {
            errHalt(F("SD card"), F("Initialisation failed!"));
        }

        Serial.println(F("SD Card initialized successfully!"));
    }

}