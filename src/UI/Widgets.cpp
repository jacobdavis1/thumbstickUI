#include "UI/Widgets.h"
#include "Display.h"


// Widget

Widget::Widget(String newName, String newText, uint16_t newTextSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor)
    : name(newName), text(newText), textSize(newTextSize), textColor(newTextColor), lineColor(newLineColor)
{
    generateDimensions();
}

void Widget::select()
{
    selected = !selected;
}

void Widget::generateDimensions()
{
    w = (text.length() * textSize * 6) + (2 * textBuffer * textSize);
    h = (textSize * 6) + (2 * textBuffer * textSize);

    textX = x + (textBuffer * textSize);
    textY = y + (textBuffer * textSize);
}

void Widget::setPosition(uint16_t newX, uint16_t newY)
{
    x = newX;
    y = newY;
    generateDimensions();
}

void Widget::draw(Display* display)
{
    if (selected)
        display->drawBox(x, y, w, h, selectedColor);
    else
        display->drawBox(x, y, w, h, lineColor);
    

    display->setTextSize(textSize);
    display->setTextColor(textColor);
    display->setCursor(textX, textY);
    display->println(text);
}


// Button

Button::Button(String newName, widgetFunc func, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor)
    : Widget(newName, newText, textSize, newTextColor, newLineColor, newSelectedColor), payload(func)
{

}

Button::~Button()
{

}

void Button::activate()
{
    payload();
}

// Label

Label::Label(String newName, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor)
    : Widget(newName, newText, textSize, newTextColor, newLineColor, newSelectedColor)
{

}

Label::~Label()
{

}

void Label::draw(Display* display)
{
    display->setTextSize(textSize);
    display->setTextColor(textColor);
    display->setCursor(textX, textY);
    display->println(text);
}