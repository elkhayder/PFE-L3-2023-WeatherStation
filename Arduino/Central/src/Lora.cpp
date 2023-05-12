#include "Lora.h"
#include "helpers.h"

namespace Custom::Lora
{
    RH_RF95<HardwareSerial> rf95(Serial1);
    String buffer = "";

    void setup()
    {
        if (!rf95.init())
        {
            errHalt(F("LoRa"), F("Initialization failed"));
        }

        Serial.println("LoRa initialized successfully");
        if (!rf95.setFrequency(FREQUENCY))
        {
            errHalt(F("LoRa"), F("Failed to set frequency"));
        }
    }

    void loop()
    {
        if (rf95.available())
        {
            char buf[RH_RF95_MAX_MESSAGE_LEN];
            uint8_t len = sizeof(buf);
            if (!rf95.recv((uint8_t *)buf, &len))
            {
                Serial.println("LoRa receive failed");
                return;
            }

            for (size_t i = 0; i < len; i++)
            {
                if (buf[i] == '\n')
                {
                    parsePayload();
                    buffer = "";
                }
                else
                {
                    buffer += buf[i];
                }
            }
        }
    }

    void parsePayload()
    {

        Serial.print("Parsing: ");
        Serial.println(buffer);

        DynamicJsonDocument doc(1024);

        DeserializationError error = deserializeJson(doc, buffer);

        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }

        const char *node = doc["node"];
        const char *measure = doc["measure"];
        double value = doc["value"];

        File db = Storage::sd.open("db.csv", FILE_WRITE);

        if (!db)
        {
            errHalt(F("SD Card"), F("DB file open failed"))
        }

        db.print(node);
        db.print(",");
        db.print(measure);
        db.print(",");
        db.print(value);
        db.print(",");
        db.println(Clock::time());

        db.close();
    }
}