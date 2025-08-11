#include "WashingBear.h"
#include <iostream>

bool mouse_move_handler(WashingBear::EventData event_data) {
  std::cout << "Mouse X: " << event_data.numbers.at("xpos") << std::endl;
  return true;
}

void initGUI() {
  WashingBear::EventManager::addHandler("mouse_move", mouse_move_handler);
}
