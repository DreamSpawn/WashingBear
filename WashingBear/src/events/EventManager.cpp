#include "EventManager.h"

namespace WashingBear {
	void EventManager::registerEvent(std::string event_name) {
		Events::registerEvent(event_name);
	}

	void EventManager::triggerEvent(std::string event_name, EventData event_data) {
		Events::triggerEvent(event_name, event_data);
	}

	void EventManager::addHandler(std::string event_name, handler_func* handler) {
		Events::addHandler(event_name, handler);
	}

	void EventManager::init(GLFWwindow* window) {
		glfwSetCursorPosCallback(window, cursor_position_callback);
		Events::registerEvent("mouse_move");

		glfwSetKeyCallback(window, key_callback);
		Events::registerEvent("key_down");
		Events::registerEvent("key_up");

		glfwSetMouseButtonCallback(window, mouse_button_callback);
		Events::registerEvent("mouse_down");
		Events::registerEvent("mouse_up");
	}

	// Callbacks
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		EventData event_data;
		event_data.numbers["xpos"] = xpos;
		event_data.numbers["ypos"] = ypos;
		Events::triggerEvent("mouse_move", event_data);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		EventData event_data;
		event_data.numbers["button"] = button;

		if (action == GLFW_PRESS) {
			Events::triggerEvent("mouse_down", event_data);
		} else {
			Events::triggerEvent("mouse_up", event_data);
		}
	}
}