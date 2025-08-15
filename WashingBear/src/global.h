#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include "layer/Layer.h"

namespace WashingBear {
  extern std::string resourcePath;
  extern std::vector<Layer*> layers;

  extern int window_width;
  extern int window_height;

  extern float projection_x;
  extern float projection_y;

  extern GLuint pick_frame_buffer;
  extern GLuint pick_render_buffer;
}
