#ifndef _CUSTOM_CLOCK_H
#define _CUSTOM_CLOCK_H

#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include <RTClib.h>

#include "Poll.h"
#include "LCD.h"

namespace Custom::Clock
{

    extern uint32_t _unix_timestamp;
    extern const uint16_t _HOST_PORT;
    extern const String _HOST_NAME;
    extern const String _PATH_NAME;
    extern Custom::Poll _fetch_poll;   // 24 hours
    extern Custom::Poll _display_poll; // 1s
    extern WiFiClient _wifi;
    extern HttpClient _client;
    extern uint32_t _fetched_at;
    extern uint32_t offset; // 2 hours in seconds
    extern bool fetchedSuccess;

    void setup();
    void loop();
    void fetch();
    uint32_t time();
    void display();

}
#endif