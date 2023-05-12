#include "DHT11.h"

#include "DHT.h"

DHT11X::~DHT11X()
{
    delete _module;
}

DHT11X::DHT11X(uint8_t pin)
{
    _pin = pin;
}

void DHT11X::setup()
{
    _module = new DHT(_pin, DHT11);
    _module->begin();
    Serial.println("DHT11 (Pressure Sensor) initialized");
}

void DHT11X::run(RH_RF95<SoftwareSerial> *lora)
{

    String r1 = toJson("Humidity", _module->readHumidity());
    sendLora(r1);

    String r2 = toJson("Temperature", _module->readTemperature());
    sendLora(r2);
}