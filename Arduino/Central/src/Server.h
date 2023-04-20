#ifndef _CUSTOM_SERVER_H
#define _CUSTOM_SERVER_H

#include <WiFiNINA.h>
#include "Storage.h"
// https://github.com/lasselukkari/awot
#define LOW_MEMORY_MCU
#include <aWOT.h>

namespace Custom
{
    struct ExtMime
    {
        String ext;
        String mime;
    };

    class Server
    {
    public:
        static String STATIC_FOLDER;
        static const struct ExtMime MIMES[] PROGMEM;

    public:
        static void setup();
        static void loop();

        static const String *fileContentType(String *filename);

        static WiFiServer _server;
        static Application _app;
    };

    namespace RequestHandlers
    {
        void index(Request &req, Response &res);
        void file(Request &req, Response &res);
        void file(Request &req, Response &res, const char *filepath);
    }
}

#endif