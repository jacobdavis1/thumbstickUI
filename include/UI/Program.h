/* Program class
    The definitions of menus, buttons, and so on are determined by the 
    Program class, which encapsulates the structure of the specific
    program being run. It is what WindowManager navigates.
*/

#include <Arduino.h>
#undef min
#undef max

#include <map>
#include "Menu.h"

class Program
{
public:
    Program();
    ~Program();

    static void init();
    static void addMenu(Menu* menu);
    static void navigateToMenu(String name);
    static void setRoot(Menu* menuPtr);
    static Menu* getRoot();
    static Menu* getCurrent();

    static void setupMenus();

//private:
    inline static std::map<String, Menu*> menus;
    inline static Menu *rootMenu, *currentMenu;
};