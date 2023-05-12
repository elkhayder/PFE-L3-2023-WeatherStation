#ifndef _CUSTOM_SERVER_H
#define _CUSTOM_SERVER_H

#include <WiFiNINA.h>
#include "Storage.h"
// https://github.com/lasselukkari/awot
// #define LOW_MEMORY_MCU
#include <aWOT.h>

namespace Custom::Server
{
    struct ExtMime
    {
        String ext;
        String mime;
    };

    extern String STATIC_FOLDER;
    extern WiFiServer _server;
    extern Application _app;

    const struct ExtMime MIMES[] PROGMEM = {
        {F("html"), F("text/html")},
        {F("css"), F("text/css")},
        {F("js"), F("text/javascript")},
        {F("png"), F("image/png")},
        {F("jpeg"), F("image/jpeg")},
        {F("jpg"), F("image/jpg")},
        {F("svg"), F("image/svg+xml")},
    };

    void setup();
    void loop();
    const String *fileContentType(String *filename);

    namespace RequestHandlers
    {
        void index(Request &req, Response &res);
        void db(Request &req, Response &res);
        void staticFiles(Request &req, Response &res);
        void file(Request &req, Response &res, const char *filepath);
    }
}

#endif