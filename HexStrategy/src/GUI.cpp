#include "WashingBear.h"
#include <iostream>

extern unsigned int hex_layer;

bool mouse1_down;

bool mouse_move_handler(WashingBear::EventData event_data) {
  if (mouse1_down) {

  }
  else {
    std::vector<int> hits = WashingBear::PickGeom(event_data.numbers.at("xpos"), event_data.numbers.at("ypos"));
    WashingBear::SetSelected(hex_layer, hits.at(hex_layer));
  }
  
  return true;
}

bool mouse_down_handler(WashingBear::EventData event_data) {
  if (event_data.numbers["button"] == 1.0) {
    mouse1_down = true;
  }
  return true;
}

bool mouse_up_handler(WashingBear::EventData event_data) {
  if (event_data.numbers["button"] == 1.0) {
    mouse1_down = false;
  }
  return true;
}

void initGUI() {
  WashingBear::Events::addHandler("mouse_move", mouse_move_handler);
  WashingBear::Events::addHandler("mouse_down", mouse_down_handler);
  WashingBear::Events::addHandler("mouse_up", mouse_up_handler);
}
