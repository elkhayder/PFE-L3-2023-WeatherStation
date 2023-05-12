#include "BMP388.h"

BMP388::~BMP388()
{
    delete _module;
}

BMP388::BMP388()
{
    _module = new DFRobot_BMP388_I2C();
    _module->set_iic_addr(BMP3_I2C_ADDR_PRIM);
}

void BMP388::setup()
{
    Serial.println("Initializing BMP388 (Pressure Sensor)...");
    while (_module->begin() != BMP3_OK)
    {
        Serial.println("BMP388 initialization failed, Retrying...");
        delay(1000);
    }
    Serial.println("BMP388 initialized");
}

void BMP388::run(RH_RF95<SoftwareSerial> *lora)
{
    String result = toJson("Pressure", _module->readPressure());

    sendLora(result)
}