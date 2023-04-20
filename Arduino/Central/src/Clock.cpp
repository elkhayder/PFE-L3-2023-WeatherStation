#include "Clock.h"

namespace Custom
{
    uint32_t Clock::_unix_timestamp = 0;
    const uint16_t Clock::_HOST_PORT = 80;
    const String Clock::_HOST_NAME = F("www.worldtimeapi.org");
    const String Clock::_PATH_NAME = F("/api/timezone/Europe/Paris");
    Custom::Poll Clock::_poll(24 * 60 * 60 * 1000); // 24 hours
    WiFiClient Clock::_wifi = WiFiClient();
    HttpClient Clock::_client = HttpClient(_wifi, _HOST_NAME);
    uint32_t Clock::_fetched_at = 0;

    void Clock::loop()
    {
        if (!_poll.shouldExecute())
            return;

        fetch();
    }

    void Clock::fetch()
    {

        // Normally, this should require just around 512 Bytes, but for some reason, it throws a NoMemory error. So i'm allocating 1K Bytes, it should'nt be a problem since we free it at the end of the call
        DynamicJsonDocument json(1024);

        _poll.duration = 60 * 60 * 1000; // 1min
        _poll.setExecuted();

        Serial.println(F("Getting time"));

        _client.get(_PATH_NAME);

        int statusCode = _client.responseStatusCode();

        if (statusCode < 200 || statusCode >= 300)
        {
            Serial.print(F("Getting time failed with status code: "));
            Serial.println(statusCode);
            return;
        }

        String response = _client.responseBody();

        _client.stop();

        DeserializationError error = deserializeJson(json, response.c_str());

        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }

        _poll.duration = 24 * 60 * 60 * 1000; // 24h

        _unix_timestamp = json["unixtime"];
        _fetched_at = millis();

        Serial.println(F("Time fetched successfully"));

        Serial.print(F("Current timestamp: "));
        Serial.println(_unix_timestamp);
    }

    uint32_t Clock::time()
    {
        return _unix_timestamp + (millis() - _fetched_at) / 1000;
    }
}