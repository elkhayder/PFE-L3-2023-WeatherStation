#ifndef _CUSTOM_LCD_H
#define _CUSTOM_LCD_H

#include <LiquidCrystal_I2C.h>
#include <WiFiNINA.h>

namespace Custom::LCD
{
    extern LiquidCrystal_I2C _instance;
    extern const char empty_line[] PROGMEM; // 20 empty character

    void setup();
    void clearLine(uint8_t l);
    void printStringCenter(String s, uint8_t y);

    void printError(String _module, String err);
}

#endif