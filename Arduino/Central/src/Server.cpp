#include "Server.h"

namespace Custom
{
    String Server::STATIC_FOLDER = F("website");
    WiFiServer Server::_server(80);
    Application Server::_app = Application();
    const struct ExtMime Server::MIMES[] PROGMEM = {
        {F("html"), F("text/html")},
        {F("css"), F("text/css")},
        {F("js"), F("text/javascript")},
        {F("png"), F("image/png")},
        {F("jpeg"), F("image/jpeg")},
        {F("jpg"), F("image/jpg")},
        {F("svg"), F("image/svg+xml")},
    };

    void Server::setup()
    {

        Serial.println(F("Initiating Server"));

        _server.begin();

        // Register routes

        _app.get("/", &RequestHandlers::index); // Index page
        for (size_t i = 0; i < Storage::files_count; i++)
        {
            _app.get(Storage::files[i], &RequestHandlers::file); // SD files
        }
    }

    void Server::loop()
    {
        WiFiClient client = _server.available();
        if (client.available())
        {
            _app.process(&client);
            client.stop();
        }
    }

    const String *Server::fileContentType(String *filename)
    {

        for (int i = 0; i < sizeof(MIMES); i++)
        {
            if (filename->endsWith(MIMES[i].ext))
            {
                return &MIMES[i].mime;
            }
        }

        return NULL;
    }

    namespace RequestHandlers
    {
        void index(Request &req, Response &res)
        {
            file(req, res, "index.html");
        }

        void file(Request &req, Response &res)
        {
            file(req, res, req.path());
        }

        void file(Request &req, Response &res, const char *filename)
        {
            String filepath = Server::STATIC_FOLDER + "/" + filename;

            if (!Storage::sd.exists(filepath))
            {
                Serial.println(F("File not found"));
                res.sendStatus(404);
                return;
            }

            File file = Storage::sd.open(filepath);

            const String *contentType = Server::fileContentType(&filepath);

            if (contentType != NULL)
            {
                res.set("Content-Type", contentType->c_str());
            }

            while (file.available())
            {
                res.write(file.read());
            }

            file.close();
            return;
        }
    }
}