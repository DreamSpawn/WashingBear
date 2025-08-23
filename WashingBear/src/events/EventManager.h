#pragma once
#include "Events.h"
#include <GLFW/glfw3.h>


namespace WashingBear {

  class EventManager {
    public:
      static void registerEvent(std::string event_name);
      static void triggerEvent(std::string event_name, EventData event_data);
      static void addHandler(std::string evet_name, handler_func*);
      static void init(GLFWwindow* window);
  };

  // Callbacks
  static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
}