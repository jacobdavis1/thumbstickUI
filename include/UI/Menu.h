/* Menu class
    Holds an arrangement of widgets and provides navigation between buttons.
*/

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <map>
#include "Widgets.h"

class Display;

class Menu : public Widget
{
public:
    friend class Program;

    Menu(String name, uint16_t newSlotsW = 5, uint16_t newSlotsH = 5, uint16_t newX = 0, uint16_t newY = 0, uint16_t newW = 320, uint16_t newH = 240);
    ~Menu();

    void update();
    void draw(Display* display);

    // Navigation
    void updateNeighbors();
    Widget* findNeighbor(uint16_t slotX, uint16_t slotY, int16_t xDir, int16_t yDir = 0);
    Widget* getFirstWidget();
    Widget* getWidgetByName(String name);
    Widget* getWidgetByIndex(uint16_t i);
    int getWidgetIndexByName(String name);

    // Widgets
    void addWidget(Widget* widget, uint16_t slotX, uint16_t slotY, uint16_t slotW, uint16_t slotH);

//private:
    std::vector<Widget*> widgets;
    std::vector<std::vector<Widget*>> navigation;
    uint16_t slotsW, slotsH;
};

#endif