
#ifndef CONSOLE_H
#define CONSOLE_H
// Arduino.h defines min and max, which conflict with std
#include <Arduino.h>
#undef min
#undef max

#include <deque>

class Display;

class Console
{
public:
    Console(Display* displayPtr);
    ~Console();

    void print(String s);

    void draw();

private:
    const int maxSize = 10;
    Display* display;
    std::deque<String> messages;
    bool changed;
};
#endif