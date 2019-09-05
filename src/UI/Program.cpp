#include "UI/Program.h"

Program::Program()
{
    setupMenus();
}

Program::~Program()
{

}

void Program::addMenu(Menu menu, String name)
{
    Program::menus[name] = menu;
}

void Program::navigateToMenu(String name)
{
    Menu* m = &menus[name];
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
    Menu mainPage;
    {
        mainPage.addButton("Left Button", [](){}, 20, 20);
        mainPage.addButton("Right Button", [](){}, 200, 20);
        mainPage.addButton("Left Button 2", [](){}, 20, 80);
        mainPage.addButton("Right Button 2", [](){}, 200, 80);
        mainPage.addButton("Left Button 3", [](){}, 20, 100);
        mainPage.addButton("To Side Pg", [](){ navigateToMenu("Side Page"); }, 200, 100);

        mainPage.updateNavGraph("Left Button", "", "", "Right Button", "", "Left Button 2", "", "", "");
        mainPage.updateNavGraph("Right Button", "", "", "", "", "Right Button 2", "", "Left Button", "");
        mainPage.updateNavGraph("Left Button 2", "Left Button", "", "Right Button 2", "", "Left Button 3", "", "", "");
        mainPage.updateNavGraph("Right Button 2", "Right Button", "", "", "", "To Side Pg", "", "Left Button 2", "");
        mainPage.updateNavGraph("Left Button 3", "Left Button 2", "", "To Side Pg", "", "", "", "", "");
        mainPage.updateNavGraph("To Side Pg", "Right Button 2", "", "", "", "", "", "Left Button 3", "");
        addMenu(mainPage, "Main Page");
    }

    Menu sidePage;
    {
        sidePage.addButton("Back", [](){ navigateToMenu("Main Page"); }, 100, 100);
        addMenu(sidePage, "Side Page");
    }

    rootMenu = &menus["Main Page"];
    currentMenu = rootMenu;
}