#ifndef _BMT388_H
#define _BMP388_H

#include <bmp3_defs.h>
#include <DFRobot_BMP388.h>
#include <DFRobot_BMP388_I2C.h>

#include "_Sensor.h"

class BMP388 : public Sensor
{

public:
    BMP388();
    ~BMP388();

    void setup() override;
    void run(RH_RF95<SoftwareSerial> *lora) override;

private:
    DFRobot_BMP388_I2C *_module = NULL;
};

#endif