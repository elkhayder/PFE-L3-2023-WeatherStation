#ifndef _CUSTOM_WIFI_H
#define _CUSTOM_WIFI_H

#include <WiFiNINA.h>
#include "Poll.h"
#include "LCD.h"

namespace Custom::WiFi
{

    extern const char *_ssid, *_password; //  Should be designed in .ino file

    extern uint8_t _status;
    extern Poll _status_poll;
    extern IPAddress local_ip;

    void setup();
    void loop();
    void connect();
    void verifyConnectionStatus();

}
#endif