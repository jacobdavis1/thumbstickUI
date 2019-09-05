/* Menu class
    Holds an arrangement of widgets and provides navigation between buttons.
*/

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <map>
#include "Widgets.h"

class Display;

struct NavNode
{
    String name;
    Widget* thisWidget;
    NavNode* neighbors[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
};

class Menu
{
public:
    friend class Program;

    Menu();
    ~Menu();

    void update();
    void draw(Display* display);

    // NavGraph
    bool updateNavGraph(String name, String n, String ne, String e, String se, String s, String sw, String w, String nw);
    NavNode* getFirstNode();
    NavNode* getNodeByName(String name);

    // Widgets
    NavNode* addButton(String name, widgetFunc func, uint16_t newX, uint16_t newY);
    NavNode* addButton(String newName, widgetFunc func, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newSelectedColor, uint16_t newLineColor, uint16_t newX, uint16_t newY);
    NavNode* addLabel(String name, String text, uint16_t newX, uint16_t newY);
    NavNode* addLabel(String newName, String newText, uint16_t textSize, uint16_t newTextColor, uint16_t newLineColor, uint16_t newSelectedColor, uint16_t newX, uint16_t newY);

//private:
    std::map<String, Widget*> widgets;
    std::vector<NavNode> navGraph;
    String name;
};

#endif