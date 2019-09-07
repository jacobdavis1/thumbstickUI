#include <Arduino.h>
#include "Thumbstick.h"
#include "Display.h"
#include "OS/Console.h"
#include "OS/Scheduler.h"
#include "UI/Menu.h"
#include "UI/Program.h"

Menu* currentMenu;
Widget* currentWidget;

Display display(320, 240);
Console console(&display);
Thumbstick thumb(4, 3, 6, 5, 2, [] () { currentWidget->activate(); });
Scheduler scheduler;
bool thumbSw = false;

void setup() {
  Program::setupMenus();
  currentMenu = Program::getCurrent();
  currentWidget = currentMenu->getFirstWidget();
  currentWidget->select();

  display.fillScreen(COLOR_BLUE);
  console.print("Test begin.");
  /*if (currentMenu == nullptr) console.print("Null menu!");
  if (currentMenu->widgets.size() == 0) console.print("No widgets!");
  console.print(String(currentMenu->widgets.at(0)->w));
  
  for (int j = 0; j < currentMenu->slotsW; ++j) 
  {
    String l;

    for (int i = 0; i < currentMenu->slotsH; ++i)
    {
      l += (String)((currentMenu->navigation.at(i).at(j) == nullptr) ? "N/A, " : "WID, ");
    }

    console.print(l);
  }

  for (int w = 0; w < currentMenu->widgets.size(); ++w)
  {
    String s = currentMenu->widgets.at(w)->name;
    s += ":  ";

    for (int i = 0; i < 8; ++i)
    {
      s += (String)((currentMenu->widgets.at(w)->neighbors[i] == nullptr) ? "NO, " : "WG, ");
    }

    console.print(s);
  }*/
  

  scheduler.scheduleTask(100, true, [](){
    //console.draw();
    Program::getCurrent()->draw(&display);
  });

  // Menu interaction
  scheduler.scheduleTask(85, true, [](){
    // Thumbstick press, maybe events in future
    thumb.update();
    
    int dir = (int)thumb.getDirection();
    console.print((String)dir);
    if (dir > 0 && currentWidget && currentWidget->neighbors[dir - 1] != nullptr)
    {
      currentWidget->select();
      currentWidget = currentWidget->neighbors[dir - 1];
      currentWidget->select();
    }

    if (currentMenu != Program::getCurrent())
    {
      currentWidget->select();
      currentMenu = Program::getCurrent();
      currentWidget = currentMenu->getFirstWidget();
      currentWidget->select();

      display.fillScreen(COLOR_BLUE);
    }
  });
}

void loop() {
  scheduler.update();
}