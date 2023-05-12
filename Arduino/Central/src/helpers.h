#ifndef _HELPERS_H
#define _HELPERS_H

#include "LCD.h"

#define errHalt(_module, _err)      \
    Serial.print(_module);          \
    Serial.print(": ");             \
    Serial.println(_err);           \
    LCD::printError(_module, _err); \
    while (true)                    \
        yield();

#endif