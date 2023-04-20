#include "WiFi.h"

namespace Custom
{

        uint8_t WiFi::_status = WL_IDLE_STATUS;
        Poll WiFi::_status_poll(10 * 60 * 1000);
        IPAddress WiFi::local_ip = IPAddress(0, 0, 0, 0);

        void WiFi::setup()
        {
                if (::WiFi.status() == WL_NO_MODULE)
                {

                        Serial.println(F("No WiFi Module detected"));

                        while (true)
                                ;
                }

                String fv = ::WiFi.firmwareVersion();

                Serial.print(F("Wifi Module detected, firmware version: "));
                Serial.println(fv);

                connect();
        }

        void WiFi::loop()
        {
                if (!_status_poll.shouldExecute())
                        return;

                verifyConnectionStatus();
                _status_poll.setExecuted();
        }

        void WiFi::verifyConnectionStatus()
        {
                _status = ::WiFi.status();

                Serial.println(F("Verifying WiFi connection"));

                if (_status != WL_CONNECTED)
                {

                        Serial.println(F("WiFi Connection lost"));

                        connect();
                }

                else
                {
                        Serial.println(F("Still connected"));
                }
        }

        void WiFi::connect()
        {
                while (_status != WL_CONNECTED)
                {

                        Serial.print(F("Connecting to WiFi: "));
                        Serial.print(_ssid);

                        _status = ::WiFi.begin(_ssid, _password);

                        delay(5000); // Wait up to 5s for connection to establish
                }
                local_ip = ::WiFi.localIP();

                Serial.println(F("WIFI Connected"));
                Serial.print(F("Local IP: "));
                Serial.println(local_ip);
                Serial.print(F("RSSI: "));
                Serial.println(::WiFi.RSSI());
        }
}