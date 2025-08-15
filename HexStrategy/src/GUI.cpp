#include "WashingBear.h"
#include <iostream>

extern unsigned int hex_layer;

bool mouse_move_handler(WashingBear::EventData event_data) {

  std::vector<int> hits = WashingBear::PickGeom(event_data.numbers.at("xpos"), event_data.numbers.at("ypos"));
  WashingBear::SetSelected(hex_layer, hits.at(hex_layer));
  
  return true;
}

void initGUI() {
  WashingBear::EventManager::addHandler("mouse_move", mouse_move_handler);
}
