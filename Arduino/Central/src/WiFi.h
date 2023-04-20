#ifndef _CUSTOM_WIFI_H
#define _CUSTOM_WIFI_H

#include <WiFiNINA.h>
#include "Poll.h"

namespace Custom
{
    class WiFi
    {

    public:
        static void setup();
        static void loop();
        static void connect();
        static void verifyConnectionStatus();

        static const char *_ssid, *_password;

        static uint8_t _status;

        static Poll _status_poll;

        static IPAddress local_ip;
    };

}
#endif