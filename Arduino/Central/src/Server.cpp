#include "Server.h"

namespace Custom::Server
{

    String STATIC_FOLDER = F("website");
    WiFiServer _server(80);
    Application _app;

    void setup()
    {

        _server.begin();

        _app.get("/api/db", &RequestHandlers::db);
        _app.get(&RequestHandlers::staticFiles);
        _app.get("/", &RequestHandlers::index);
    }

    void loop()
    {
        WiFiClient client = _server.available();
        if (client.available())
        {
            _app.process(&client);
            client.stop();
        }
    }

    const String *fileContentType(String *filename)
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

        void staticFiles(Request &req, Response &res)
        {
            if (strlen(req.path()) == 1) // "/"
            {
                return file(req, res, "/index.html");
            }

            return file(req, res, req.path());
        }

        void db(Request &req, Response &res)
        {
            Serial.println("db");
            File file = Storage::sd.open("db.csv");

            if (!file)
            {
                // res.sendStatus(404);
                return;
            }

            // res.set("Content-Type", "text/csv");

            while (file.available())
            {
                res.write(file.read());
            }

            file.close();

            res.end();
        }

        void file(Request &req, Response &res, const char *filename)
        {
            String filepath = Server::STATIC_FOLDER + filename;

            if (!Storage::sd.exists(filepath))
            {
                res.sendStatus(404);
                return;
            }

            File file = Storage::sd.open(filepath);

            if (file.isDirectory())
            {
                res.sendStatus(403);
                return;
            }

            const String *contentType = Server::fileContentType(&filepath);

            if (contentType != NULL)
            {
                res.set("Content-Type", contentType->c_str());
            }

            while (file.available())
            {
                res.write(file.read());
            }

            res.end();

            file.close();
            return;
        }
    }
}