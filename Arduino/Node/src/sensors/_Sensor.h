#ifndef _SENSOR_H
#define _SENSOR_H

#include <RH_RF95.h>
#include <SoftwareSerial.h>
#include "../_helpers.h"

class Sensor
{
public:
    virtual void setup() = 0;
    virtual void run(RH_RF95<SoftwareSerial> *lora) = 0;
};

#endif