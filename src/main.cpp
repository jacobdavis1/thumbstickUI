#include <Arduino.h>
#include "OS/WindowManager.h"

WindowManager windowManager;

void setup() {
  WindowManager::init();
}

void loop() {
  WindowManager::update();
  //WindowManager::console->draw();
}