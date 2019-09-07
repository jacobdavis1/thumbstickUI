#include "OS/Console.h"
#include "Display.h"

    Console::Console(Display* displayPtr) : display(displayPtr)
    {
        changed = false;
    }
   
    Console::~Console()
    {

    }

    void Console::print(String s)
    {
            messages.push_back(s);
            changed = true;

            if (messages.size() > maxSize)
                messages.pop_front();
    }

    void Console::draw()
    {
        if (changed)
        {
            display->fillRect(0, 0, display->width(), display->height(), COLOR_BLUE);
            if (messages.size() > 0)
            {
                int x = 0, y = 5;
                display->setTextColor(COLOR_WHITE);

                display->setTextSize(1);
                display->setCursor(x, y);
                display->println(messages[0]);
                y += 32;

                for (int i = 1; i < messages.size(); ++i)
                {
                    display->println(messages[i]);
                    y += 16;
                }
            }

            changed = false;
        }
    }