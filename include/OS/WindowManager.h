/* WindowManager class
    Converts input from external sources into interaction with and navigation
    through the current menu.
*/

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "UI/Program.h"
#include "UI/Menu.h"
#include "OS/Console.h"
#include "Thumbstick.h"
#include "Scheduler.h"

class WindowManager
{
public:
    static void init();
    static void update();
    static void draw();

    static void changeMenu(String newMenuName);
    static void activateSelection();

//private:
    static void printMenuDiagnostics();

    inline static Menu* currentMenu;
    inline static Widget* currentWidget;

    inline static Display* display;
    inline static Console* console;
    inline static Thumbstick* thumb;
    inline static Scheduler* scheduler;
    inline static bool thumbSw = false;
};

#endif