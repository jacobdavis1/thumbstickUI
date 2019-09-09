#include "UI/Menu.h"
#include "OS/WindowManager.h"
#include "Display.h"

Menu::Menu(String name, uint16_t newSlotsW, uint16_t newSlotsH, uint16_t newX, uint16_t newY, uint16_t newW, uint16_t newH) 
    : Widget(name), slotsW(newSlotsW), slotsH(newSlotsH)
{
    x = newX;
    y = newY;
    w = newW;
    h = newH;

    for (int i = 0; i < slotsW; ++i)
    {
        navigation.push_back(std::vector<Widget*>());

        for (int j = 0; j < slotsH; ++j)
        {
            navigation.at(i).push_back(nullptr);
        }
    }
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
    for (int i = 0; i < widgets.size(); ++i)
    {
        widgets.at(i)->draw(display);
    }
}

void Menu::updateNeighbors()
{
    for (int i = 0; i < slotsW; ++i)
    {
        for (int j = 0; j < slotsH; ++j)
        {
            if (navigation.at(i).at(j) != nullptr && navigation.at(i).at(j)->slotX == i && navigation.at(i).at(j)->slotY == j)
            {
                // Check north
                if (navigation.at(i).at(j)->neighbors[0] == nullptr)
                    navigation.at(i).at(j)->neighbors[0] = findNeighbor(i, j, 0, -1);

                // Check east
                if (navigation.at(i).at(j)->neighbors[2] == nullptr)
                    navigation.at(i).at(j)->neighbors[2] = findNeighbor(i, j, 1, 0);

                // Check south
                if (navigation.at(i).at(j)->neighbors[4] == nullptr)
                    navigation.at(i).at(j)->neighbors[4] = findNeighbor(i, j, 0, 1);

                // Check north
                if (navigation.at(i).at(j)->neighbors[6] == nullptr)
                    navigation.at(i).at(j)->neighbors[6] = findNeighbor(i, j, -1, 0);
            }
        }
    }
}

Widget* Menu::findNeighbor(uint16_t slotX, uint16_t slotY, int16_t xDir, int16_t yDir)
{
    if (xDir != 0)
    {
        for (int i = slotX + xDir; i >= 0 && i < slotsW; i += xDir)
        {
            if(navigation.at(i).at(slotY) == navigation.at(slotX).at(slotY))
                break;

            if (navigation.at(i).at(slotY) != nullptr)
                return navigation.at(i).at(slotY);
        }
    }
    else if (yDir != 0)
    {
        for (int j = slotY + yDir; j >= 0 && j < slotsH; j += yDir)
        {
            if (navigation.at(slotX).at(j) == navigation.at(slotX).at(slotY))
                break;

            if (navigation.at(slotX).at(j) != nullptr)
                return navigation.at(slotX).at(j);
        }
    }

    return nullptr;
}

Widget* Menu::getFirstWidget()
{
    if (widgets.size() > 0)
        return widgets.at(0);
    else return nullptr;
}

Widget* Menu::getWidgetByName(String name)
{
    return widgets[getWidgetIndexByName(name)];
}

Widget* Menu::getWidgetByIndex(uint16_t i)
{
    if (i < widgets.size())
        return widgets.at(0);
    else return nullptr;
}

int Menu::getWidgetIndexByName(String name)
{
    for (int i = 0; i < navigation.size(); ++i)
    {
        if (widgets.at(i)->name.equals(name))
            return i;
    }

    return -1;
}

void Menu::addWidget(Widget* widget, uint16_t widgetSlotX, uint16_t widgetSlotY, uint16_t widgetSlotW, uint16_t widgetSlotH)
{
    // Claim tiles in Navigation    
    for (uint16_t i = widgetSlotX; i < widgetSlotX + widgetSlotW && i < slotsW; ++i)
    {
        for (uint16_t j = widgetSlotY; j < widgetSlotY + widgetSlotH && j < slotsH;  ++j)
        {
            navigation.at(i).at(j) = widget;
        }
    }

    // Calculate size ratios
    float xRat = w / (float)slotsW;
    float yRat = h / (float)slotsH;

    // Calculate pixel dimensions
    uint16_t pixelW = widgetSlotW * xRat, 
        pixelH = widgetSlotH * yRat, 
        pixelX = widgetSlotX * xRat, 
        pixelY = widgetSlotY * yRat;

    widget->setPosition(pixelX, pixelY);
    widget->slotX = widgetSlotX;
    widget->slotY = widgetSlotY;
    widget->slotW = widgetSlotH;
    widget->slotH = widgetSlotW;
    widget->generateDimensions();

    // Cut off text to fit width boundaries
    while (widget->w > pixelW)
    {
        widget->text.remove(widget->text.length() - 1);
        widget->generateDimensions();
    }

    widgets.push_back(widget);
    updateNeighbors();
}

