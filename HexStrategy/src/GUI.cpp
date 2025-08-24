#include "WashingBear.h"
#include <iostream>

extern unsigned int hex_layer;

bool mouse1_down;

int mouse_x;
int mouse_y;

int start_x;
int start_y;

float translate_x;
float translate_y;

int window_width;
int window_height;

float scale_x;
float scale_y;

bool mouse_move_handler(WashingBear::EventData event_data) {
  mouse_x = event_data.numbers.at("xpos");
  mouse_y = event_data.numbers.at("ypos");
  
  if (mouse1_down) {
    float diff_x = ( mouse_x - start_x ) / scale_x / window_width * 2;
    float diff_y = ( mouse_y - start_y ) / scale_y / window_height * 2;

    WashingBear::SetTranslation(hex_layer, translate_x + diff_x, translate_y - diff_y);
  }
  else {
    std::vector<int> hits = WashingBear::PickGeom(mouse_x, mouse_y);
    WashingBear::SetSelected(hex_layer, hits.at(hex_layer));
  }
  
  return true;
}

bool mouse_down_handler(WashingBear::EventData event_data) {
  if (event_data.numbers["button"] == 1.0) {
    mouse1_down = true;
    start_x = mouse_x;
    start_y = mouse_y;
    //WashingBear::ToggleCursor(false);
  }
  return true;
}

bool mouse_up_handler(WashingBear::EventData event_data) {
  if (event_data.numbers["button"] == 1.0) {
    mouse1_down = false;
    translate_x += (mouse_x - start_x) / scale_x / window_width * 2;
    translate_y -= (mouse_y - start_y) / scale_y / window_height * 2;
    //WashingBear::ToggleCursor(true);
  }
  return true;
}

void initGUI(int width, int height) {
  WashingBear::Events::addHandler("mouse_move", mouse_move_handler);
  WashingBear::Events::addHandler("mouse_down", mouse_down_handler);
  WashingBear::Events::addHandler("mouse_up", mouse_up_handler);

  window_width = width;
  window_height = height;

  scale_x = 1.0;
  scale_y = 1.0;
  
  if (width > height) {
    scale_x = (float) height / width;
  } else {
    scale_y = (float) width / height;
  }

  translate_x = -scale_x;
  translate_y = scale_y;

  WashingBear::SetTranslation(hex_layer, translate_x, translate_y);
}
