/* Widget class and subclasses
    These widgets are used by UIBuilder to create functional menus.
*/

#ifndef WIDGETS_H
#define WIDGETS_H
#include <Arduino.h>
#include "Display.h"

typedef void(*widgetFunc) ();

class Widget
{
public:
    Widget(String newName, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor);
    ~Widget();

    void select();
    virtual void setPosition(uint16_t newX, uint16_t newY);
    virtual void activate() { };
    virtual void draw(Display* display);

    void generateDimensions();

protected:
    String name, text;
    bool selected = false;
    uint16_t x, y, w, h, textBuffer = 3;
    uint16_t textX, textY, textSize, textColor, lineColor, selectedColor;
};

class Button : public Widget
{
public:
    Button(String newName, widgetFunc func, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor);
    ~Button();

    void activate();

private:
    widgetFunc payload;
};

class Label : public Widget
{
public:
    Label(String newName, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor);
    ~Label();

    void draw(Display* display);

private:
};

#endif