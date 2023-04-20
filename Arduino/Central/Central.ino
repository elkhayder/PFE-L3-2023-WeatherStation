#define DEBUG 1

#include "src/WiFi.h"
#include "src/Server.h"
#include "src/Clock.h"
#include "src/Storage.h"

const char *Custom::WiFi::_ssid = "TestNetwork";
const char *Custom::WiFi::_password = "00000000";

void setup()
{
    Serial.begin(115200);

    Serial.println(F("Type anything to start"));

    while (!Serial.available())
    {
        yield();
    }

    // Storage
    Custom::Storage::setup();

    // WiFi
    Custom::WiFi::setup();

    // Server
    Custom::Server::setup();

    // Clock
    Custom::Clock::fetch();
}

void loop()
{
    Custom::WiFi::loop();
    Custom::Server::loop();
    Custom::Clock::loop();
}
