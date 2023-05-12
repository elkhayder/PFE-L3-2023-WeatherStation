#include "LCD.h"

namespace Custom::LCD
{

    LiquidCrystal_I2C _instance = LiquidCrystal_I2C(0x27, 20, 4);
    const char empty_line[] PROGMEM = "                    "; // 20 empty character

    void setup()
    {
        _instance.init();
        _instance.backlight();
        _instance.clear();
    }

    void clearLine(uint8_t l)
    {
        _instance.setCursor(0, l);
        _instance.print(empty_line);
        _instance.setCursor(0, l);
    }

    void printStringCenter(String s, uint8_t y)
    {
        uint8_t x = 0;
        if (s.length() < 20)
        {
            x = (20 - s.length()) / 2;
        }
        _instance.setCursor(x, y);
        _instance.print(s);
    }

    void printError(String _module, String err)
    {
        _instance.clear();
        printStringCenter(F("Error"), 0);
        printStringCenter(_module, 1);
        printStringCenter(err, 2);

        _instance.setCursor(0, 2);
    }

}