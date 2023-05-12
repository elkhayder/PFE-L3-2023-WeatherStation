#include "Clock.h"

namespace Custom::Clock
{

    uint32_t _unix_timestamp = 0;
    const uint16_t _HOST_PORT = 80;
    const String _HOST_NAME = F("www.worldtimeapi.org");
    const String _PATH_NAME = F("/api/timezone/Europe/Paris");
    Custom::Poll _fetch_poll(24 * 60 * 60 * 1000); // 24 hours
    Custom::Poll _display_poll(1000);              // 1s
    WiFiClient _wifi = WiFiClient();
    HttpClient _client = HttpClient(_wifi, _HOST_NAME);
    uint32_t _fetched_at = 0;
    uint32_t offset = 2 * 60 * 60; // 2 hours in seconds
    bool fetchedSuccess = false;

    void loop()
    {
        if (_fetch_poll.shouldExecute())
            fetch();

        if (_display_poll.shouldExecute())
            display();
    }

    void fetch()
    {

        // Normally, this should require just around 512 Bytes, but for some reason, it throws a NoMemory error. So i'm allocating 1K Bytes, it should'nt be a problem since we free it at the end of the call
        DynamicJsonDocument json(1024);

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

        _unix_timestamp = json["unixtime"];
        _fetched_at = millis();
        fetchedSuccess = true;

        _fetch_poll.setExecuted();
        display();
    }

    uint32_t time()
    {
        return _unix_timestamp + (millis() - _fetched_at) / 1000;
    }

    void display()
    {
        LCD::_instance.setCursor(0, 3);

        if (!fetchedSuccess)
        {
            LCD::_instance.print("Error fetching time");
        }

        DateTime date(time() + offset);
        char buffer[] = "DD/MM/YYYY hh:mm:ss ";
        date.toString(buffer);
        LCD::_instance.print(buffer);
        _display_poll.setExecuted();
    }

}