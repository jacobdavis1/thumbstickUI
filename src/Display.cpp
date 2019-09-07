#include <exception>
#include "Display.h"

    uint16_t Display::defaultTextColor;
    uint16_t Display::defaultLineColor;
    uint16_t Display::defaultSelectColor;
    uint16_t Display::defaultBgColor;

    Display::Display(int w, int h) : Sipeed_ST7789(w, h, initspi)
    {
        if (!begin(15000000, COLOR_BLUE))
            throw std::exception();

        Display::defaultTextColor = COLOR_WHITE;
        Display::defaultLineColor = COLOR_WHITE;
        Display::defaultSelectColor = COLOR_RED;
        Display::defaultBgColor = COLOR_BLUE;
    }

    Display::~Display()
    {
        
    }

    void Display::drawBox(int x, int y, int w, int h, uint16_t color)
    {
        drawFastHLine(x, y, w, color);
        drawFastHLine(x, y + h, w, color);
        drawFastVLine(x, y, h, color);
        drawFastVLine(x + w, y, h, color);
    }