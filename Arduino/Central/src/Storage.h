#ifndef _STORAGE_H
#define _STORAGE_H

#include <SPI.h>
#include <SdFat.h>

#include "WiFi.h"

#define FILES_LIST_CAPACITY 20
#define FILE_NAME_CAPACITY 64

namespace Custom
{
    typedef struct FileDescription
    {
        String path;
        size_t size;
    } FileDescription;

    class Storage
    {
    public:
        static size_t files_count;
        static char files[FILES_LIST_CAPACITY][FILE_NAME_CAPACITY];
        static SdFat sd;

        static void setup();
        static int mem();
        static void readFolderContent(File dir, String prefix);
    };
}

#endif