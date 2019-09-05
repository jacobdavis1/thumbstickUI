//Direction direction = Direction::NONE;

#include <Arduino.h>
#include "Thumbstick.h"

Thumbstick::Thumbstick(int lPin, int rPin, int uPin, int dPin,  int switchPin, clickCallback func) : 
    THUMBL(lPin), THUMBR(rPin), THUMBU(uPin), THUMBD(dPin), THUMBSW(switchPin), onClickFunc(func)
{
    pinMode(THUMBL, INPUT);
    pinMode(THUMBR, INPUT);
    pinMode(THUMBU, INPUT);
    pinMode(THUMBD, INPUT);

    pinMode(THUMBSW, INPUT_PULLUP);
    pressed = false;
}

Thumbstick::~Thumbstick()
{

}

ThumbstickDirection Thumbstick::getDirection()
{
    ThumbstickDirection hor = getX(), ver = getY();

    // X axis is not centered
    if (hor != ThumbstickDirection::NONE)
    {
        switch (ver)
        {
        case ThumbstickDirection::N:
            if (hor == ThumbstickDirection::W)
                return ThumbstickDirection::NW;
            else if (hor == ThumbstickDirection::E)
                return ThumbstickDirection::NE;
        break;

        case ThumbstickDirection::S:
            if (hor == ThumbstickDirection::W)
                return ThumbstickDirection::SW;
            else if (hor == ThumbstickDirection::E)
                return ThumbstickDirection::SE;
        break;

        default:
            return hor;
        }
    }
    // X axis is centered
    else
    {
        if (ver != ThumbstickDirection::NONE)
            return ver;
        else return ThumbstickDirection::NONE;
    }
    

    return ThumbstickDirection::NONE;
}

bool Thumbstick::hasActivity()
{
    return (getX() != ThumbstickDirection::NONE || getY() != ThumbstickDirection::NONE);
}

void Thumbstick::update()
{
    if (switchPressed() && !pressed)
    {
        onClick();
        pressed = true;
    } 
    else if (!switchPressed() && pressed)
    {
        pressed = false;
    }
}

ThumbstickDirection Thumbstick::getX()
{
    if (digitalRead(THUMBR) == HIGH)
        return ThumbstickDirection::E;
    else if (digitalRead(THUMBL) == HIGH)
        return ThumbstickDirection::W;
    else return ThumbstickDirection::NONE;
}

ThumbstickDirection Thumbstick::getY()
{
    if (digitalRead(THUMBD) == HIGH)
        return ThumbstickDirection::S;
    else if (digitalRead(THUMBU) == HIGH)
        return ThumbstickDirection::N;
    else return ThumbstickDirection::NONE;
}

bool Thumbstick::switchPressed()
{
    return (digitalRead(THUMBSW) == LOW);
}

void Thumbstick::onClick()
{
    this->onClickFunc();
}