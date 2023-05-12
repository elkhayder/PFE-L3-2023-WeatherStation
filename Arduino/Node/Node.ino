
#include "src/sensors/_Sensor.h"
#include "src/sensors/DHT11.h"
#include "src/sensors/BMP388.h"

Sensor *sensors[] = {
    new DHT11X(3),
    new BMP388(),
};

const size_t sensorsCount = sizeof(sensors) / sizeof(Sensor);

SoftwareSerial loraSerial(9, 10);
RH_RF95<SoftwareSerial> lora(loraSerial);

void setup()
{
    Serial.begin(115200);

    Serial.println("Initializing RF95 (LoRa Module)...");

    while (!lora.init())
    {
        Serial.println("RF95 initialization failed, Retrying...");
        delay(1000);
    }

    if (!lora.setFrequency(864.0))
    {
        Serial.println("RF95 frequency out of range");
        while (1)
            yield();
    }

    Serial.println("RF95 initialized");

    // Setup Sensors
    for (Sensor *sensor : sensors)
    {
        sensor->setup();
    }
}

void loop()
{
    for (Sensor *sensor : sensors)
    {
        sensor->run(&lora);
    }

    // delay(5000);
    delay(30 * 30 * 60 * 1000); // 30min
}
