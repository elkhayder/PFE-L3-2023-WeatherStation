#include "Storage.h"

namespace Custom
{
    size_t Storage::files_count = 0;
    char Storage::files[FILES_LIST_CAPACITY][FILE_NAME_CAPACITY];
    SdFat Storage::sd;

    void Storage::setup()
    {

        // SD
        if (!sd.begin(SdSpiConfig(4, DEDICATED_SPI, SD_SCK_MHZ(50))))
        {

            Serial.println(F("SD Card initialisation failed!"));

            while (1)
                ;
        }

        Serial.println(F("SD Card initialized successfully!"));

        if (!files)
        {
            Serial.println(F("Error allocating Memory"));
            while (true)
                ;
        }

        File root = sd.open("website");

        Serial.println(F("Discovering files..."));
        readFolderContent(root, "/");
    }

    void Storage::readFolderContent(File dir, String prefix)
    {

        while (true)
        {
            File entry = dir.openNextFile();

            if (!entry)
            {
                // No more files
                break;
            }

            char name[255];

            entry.getName(name, 255);

            String path = prefix + name;

            if (entry.isDirectory())
            {
                readFolderContent(entry, path + "/");
            }
            else
            {
                Serial.print(F("Discovered file: "));
                Serial.println(path);

                strlcpy(files[files_count], path.c_str(), FILE_NAME_CAPACITY);

                files_count++;
            };

            entry.close();
        }
    }

    int Storage::mem()
    {
        int size = 32 * 1024;
        byte *buf;
        while ((buf = (byte *)malloc(--size)) == NULL)
            ;
        free(buf);
        return size;
    }
}