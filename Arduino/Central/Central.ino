#include "src/WiFi.h"
#include "src/Server.h"
#include "src/Clock.h"
#include "src/Storage.h"
#include "src/LCD.h"
#include "src/Lora.h"

using namespace Custom;

// TODO read these values from storage
const char *WiFi::_ssid = "TestNetwork";
const char *WiFi::_password = "00000000";

void setup()
{
    Serial.begin(115200);

    // while (!Serial)
    //     yield();

    // LCD
    LCD::setup();

    // Storage
    Storage::setup();

    // LoRa
    Lora::setup();

    // WiFi
    WiFi::setup();

    // Server
    Custom::Server::setup();

    // Clock
    Clock::fetch();
}

void loop()
{
    // WiFi::loop();
    Custom::Server::loop();
    Clock::loop();
    Lora::loop();
}
