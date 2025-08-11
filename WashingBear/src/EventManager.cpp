#include "EventManager.h"

namespace WashingBear {
	void EventManager::registerEvent(std::string event_name) {
		if (!handlers.contains(event_name)) {
			handlers[event_name] = std::vector<handler_func*>();
		}
	}

	void EventManager::triggerEvent(std::string event_name, EventData event_data) {
		if (!handlers.contains(event_name)) return;

		event_data.text["event_name"] = event_name;

		for (auto it = handlers.at(event_name).rbegin(); it != handlers.at(event_name).rend(); it++) {
			(*it)(event_data);
		}
	}

	void EventManager::addHandler(std::string event_name, handler_func* handler) {
		if (!handlers.contains(event_name)) {
			handlers[event_name] = std::vector<handler_func*>();
		}

		handlers.at(event_name).push_back(handler);
	}

	std::map<std::string, std::vector<handler_func*>> EventManager::handlers = std::map<std::string, std::vector<handler_func*>>();
}