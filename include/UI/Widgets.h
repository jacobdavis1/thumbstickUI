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
    friend class Menu;

    Widget* neighbors[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

    Widget(String newName, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor);
    Widget(String newName);
    ~Widget();

    virtual void select();
    virtual void setPosition(uint16_t newX, uint16_t newY);
    virtual void activate() { };
    virtual void draw(Display* display);

    virtual void generateDimensions();

protected:
    String name, text;
    bool selected = false;
    uint16_t x, y, w, h, textBuffer = 3;
    uint16_t textX, textY, textSize, textColor, lineColor, selectedColor;
    uint16_t slotX, slotY, slotW, slotH;
};

class Button : public Widget
{
public:
    Button(String newName, widgetFunc func, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor);
    Button(String newName, widgetFunc func);
    ~Button();

    void activate();

private:
    widgetFunc payload;
};

class Label : public Widget
{
public:
    Label(String newName, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor);
    Label(String newName);
    ~Label();

    void draw(Display* display);

private:
};

class DigitalOutSwitch : public Widget
{
public:
    DigitalOutSwitch(String newName, uint16_t pinNumber, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor, uint16_t newOnColor, uint16_t newOffColor);
    DigitalOutSwitch(String newName, uint16_t pinNumber);
    ~DigitalOutSwitch();

    void draw(Display* display);
    void activate();

    void generateDimensions();

private:
    uint16_t pinNumber = 7, onColor, offColor;
    bool pinActive = false;
};

#endif