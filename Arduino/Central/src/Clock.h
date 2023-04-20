#ifndef _CLOCK_H
#define _CLOCK_H

#include <WiFiNINA.h>
#include <ArduinoJson.h>
#define LOGGING
#include <ArduinoHttpClient.h>

#include "Poll.h"

namespace Custom
{

    class Clock
    {

    public:
        static void setup();
        static void loop();
        static void fetch();
        static uint32_t time();

    private:
        static const uint16_t _HOST_PORT;
        static const String _HOST_NAME;
        static const String _PATH_NAME;
        static WiFiClient _wifi;
        static HttpClient _client;
        static Custom::Poll _poll;
        static uint32_t _unix_timestamp;
        static uint32_t _fetched_at;
    };

}
#endif