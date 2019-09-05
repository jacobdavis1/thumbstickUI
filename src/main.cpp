#include <Arduino.h>
#include "Thumbstick.h"
#include "Display.h"
#include "OS/Console.h"
#include "OS/Scheduler.h"
#include "UI/Menu.h"
#include "UI/Program.h"

Menu* current;
NavNode* currentNode;

Display display(320, 240);
Console console(&display);
Thumbstick thumb(4, 3, 6, 5, 2, [] () { currentNode->thisWidget->activate(); });
Scheduler scheduler;

void setup() {
  Program::setupMenus();
  current = Program::getCurrent();
  currentNode = current->getFirstNode();
  currentNode->thisWidget->select();

  if (current == nullptr) console.print("Null!");
  display.fillScreen(COLOR_BLUE);

  scheduler.scheduleTask(100, true, [](){
    Program::getCurrent()->draw(&display);
    console.draw();
  });

  scheduler.scheduleTask(85, true, [](){
    thumb.update();
    int dir = (int)thumb.getDirection();
    if (dir > 0 && currentNode->neighbors[dir - 1] != nullptr)
    {
      currentNode->neighbors[dir - 1]->thisWidget->select();
      currentNode->thisWidget->select();
      currentNode = currentNode->neighbors[dir - 1];
    }

    if (current != Program::getCurrent())
    {
      current = Program::getCurrent();
      currentNode->thisWidget->select();
      currentNode = current->getFirstNode();
      currentNode->thisWidget->select();
      display.fillScreen(COLOR_BLUE);
    }
  });

  scheduler.scheduleTask(200, true, [](){
    if (thumb.switchPressed())
      currentNode->thisWidget->activate();
  });
}

void loop() {
  scheduler.update();
}