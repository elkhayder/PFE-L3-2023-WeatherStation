#ifndef _HELPERS_H
#define _HELPERS_H

#include "_constants.h"

#define toJson(measure, value) "{\"node\": \"" + String(NODE_NAME) + "\", \"measure\": \"" + String(measure) + "\", \"value\": " + String(value) + "}\n"

#define sendLora(str)                                 \
    Serial.print("Sending: ");                        \
    Serial.println(str);                              \
    lora->send((uint8_t *)str.c_str(), str.length()); \
    lora->waitPacketSent();

#endif