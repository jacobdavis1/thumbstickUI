#include <exception>
#include "Display.h"

    Display::Display(int w, int h) : Sipeed_ST7789(w, h, initspi)
    {
        if (!begin(15000000, COLOR_BLUE))
            throw std::exception();
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