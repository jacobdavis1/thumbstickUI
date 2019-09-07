// Custom maixduino display wrapper

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Sipeed_ST7789.h>
#include <Maix_KPU.h>
#include "SPI.h"

static SPIClass initspi(SPI0); // Must be 0 for Maix

class Display : public Sipeed_ST7789
{
public:
    static uint16_t defaultBgColor, defaultTextColor, defaultLineColor, defaultSelectColor;

    Display(int w, int h);
    ~Display();

    void drawBox(int x, int y, int w, int h, uint16_t color);

private:
};

#endif