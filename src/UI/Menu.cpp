#include "UI/Menu.h"
#include "OS/WindowManager.h"
#include "Display.h"

/*Menu::Menu(WindowManager* newWindowManager) : windowManager(newWindowManager)
{

}*/

Menu::Menu()
{
    
}

Menu::~Menu()
{
    // Delete all widgets
}

void Menu::update()
{

}

void Menu::draw(Display* display)
{
    for (int i = 0; i < navGraph.size(); ++i)
    {
        navGraph.at(i).thisWidget->draw(display);
    }
}

bool Menu::updateNavGraph(String name, String n, String ne, String e, String se, String s, String sw, String w, String nw)
{
    String nodeNames[8] = {n, ne, e, se, s, sw, w, nw};

    for (int i = 0; i < navGraph.size(); ++i)
    {
        if (navGraph.at(i).name.equals(name))
        {
            for (int j = 0; j < 8; ++j)
            {
                if (nodeNames[j] != "")
                    navGraph.at(i).neighbors[j] = getNodeByName(nodeNames[j]);
            }

            return true;
        }
    }

    return false;
}

NavNode* Menu::getFirstNode()
{
    if (navGraph.size() > 0)
        return &navGraph.at(0);
    else return nullptr;
}

NavNode* Menu::getNodeByName(String name)
{
    for (int i = 0; i < navGraph.size(); ++i)
    {
        if (navGraph.at(i).name.equals(name))
            return &navGraph.at(i);
    }

    return nullptr;
}

NavNode* Menu::addButton(String newName, widgetFunc func, uint16_t newX, uint16_t newY)
{
    Button* b = new Button(newName, func, newName, 1, COLOR_WHITE, COLOR_WHITE, COLOR_YELLOW);
    b->setPosition(newX, newY);
    widgets[newName] = (Widget*)b;
    
    NavNode n, *p;
    n.name = newName;
    n.thisWidget = b;
    navGraph.push_back(n);

    p = &navGraph.back();
    return p;
}

NavNode* Menu::addButton(String newName, widgetFunc func, String newText, uint16_t newTextSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelctedColor, uint16_t newX, uint16_t newY)
{
    Button* b = new Button(newName, func, newText, newTextSize, newTextColor, newLineColor, newSelctedColor);
    b->setPosition(newX, newY);
    widgets[newName] = (Widget*)b;
    
    NavNode n, *p;
    n.name = newName;
    n.thisWidget = b;
    navGraph.push_back(n);

    p = &navGraph.back();
    return p;
}

NavNode* Menu::addLabel(String newName, String newText, uint16_t newX, uint16_t newY)
{
    Label* l = new Label(newName, newText, 1, COLOR_WHITE, COLOR_WHITE, COLOR_YELLOW);
    l->setPosition(newX, newY);
    widgets[newName] = (Widget*)l;
    
    NavNode n, *p;
    n.name = newName;
    n.thisWidget = l;
    navGraph.push_back(n);

    p = &navGraph.back();
    return p;
}

NavNode* Menu::addLabel(String newName, String newText, uint16_t newTextSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor, uint16_t newX, uint16_t newY)
{
    Label* l = new Label(newName, newText, newTextSize, newTextColor, newLineColor, newSelectedColor);
    l->setPosition(newX, newY);
    widgets[newName] = (Widget*)l;
    
    NavNode n, *p;
    n.name = newName;
    n.thisWidget = l;
    navGraph.push_back(n);

    p = &navGraph.back();
    return p;
}
