#include "WiFi.h"
#include "helpers.h"

namespace Custom::WiFi
{
        uint8_t _status = WL_IDLE_STATUS;
        Poll _status_poll(10 * 60 * 1000);
        IPAddress local_ip = IPAddress(0, 0, 0, 0);

        void setup()
        {
                if (::WiFi.status() == WL_NO_MODULE)
                {

                        errHalt(F("WiFi"), F("Module not found"));
                }

                String fv = ::WiFi.firmwareVersion();

                Serial.print(F("Wifi Module detected, firmware version: "));
                Serial.println(fv);

                connect();
        }

        void loop()
        {
                if (!_status_poll.shouldExecute())
                        return;

                verifyConnectionStatus();
                _status_poll.setExecuted();
        }

        void verifyConnectionStatus()
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

        void connect()
        {
                while (_status != WL_CONNECTED)
                {
                        LCD::clearLine(0);
                        LCD::printStringCenter("Connecting to WiFi", 0);

                        _status = ::WiFi.begin(_ssid, _password);

                        delay(5000); // Wait up to 5s for connection to establish
                }
                local_ip = ::WiFi.localIP();

                LCD::clearLine(0);
                LCD::_instance.print("IP: ");
                LCD::_instance.print(local_ip);
        }
}