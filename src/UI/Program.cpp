#include "UI/Program.h"

Program::Program()
{
    setupMenus();
}

Program::~Program()
{

}

void Program::addMenu(Menu* menu)
{
    Program::menus[menu->name] = menu;
}

void Program::navigateToMenu(String name)
{
    Menu* m = menus[name];
    if (m != nullptr)
        Program::currentMenu = m;
}

void Program::setRoot(Menu* menuPtr)
{
    Program::rootMenu = menuPtr;
}

Menu* Program::getRoot()
{
    return Program::rootMenu;
}

Menu* Program::getCurrent()
{
    return Program::currentMenu;
}

/*** Menu Setup Function - alter for different functionality (is the idea) ***/

void Program::setupMenus()
{
    Menu* mainPage = new Menu("Main Page", 3, 3);
    {
        mainPage->addWidget((Widget*)new Button("Left Button", [](){}), 0, 0, 1, 1);
        mainPage->addWidget((Widget*)new Button("To Side Pg", [](){ navigateToMenu("Side Page"); }), 0, 2, 2, 1);

        addMenu(mainPage);
    }

    Menu* sidePage = new Menu("Side Page", 2, 2);
    {
        sidePage->addWidget((Widget*)new Button("Back", [](){ navigateToMenu("Main Page"); }), 0, 0, 2, 2);
        addMenu(sidePage);
    }

    rootMenu = menus["Main Page"];
    currentMenu = rootMenu;
}