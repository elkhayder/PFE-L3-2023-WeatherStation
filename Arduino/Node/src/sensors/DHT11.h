#ifndef _DHT11_H
#define _DHT11_H

#include "DHT.h"

#include "_Sensor.h"

// I added X to the name to avoid name conflicting
class DHT11X : public Sensor
{
public:
    DHT11X(uint8_t pin);
    ~DHT11X();

    void setup() override;
    void run(RH_RF95<SoftwareSerial> *lora) override;

private:
    DHT *_module = NULL;
    uint8_t _pin = NULL;
};

#endif