#pragma once
#include <string>
#include <map>
#include <vector>
#include <WBtypes.h>

#ifdef WB_ENGINE
#define WB_API __declspec(dllexport)
#else
#define WB_API __declspec(dllimport)
#endif // WB_ENGINE

namespace WashingBear {
	typedef bool handler_func(EventData);

	class WB_API Events	{
	
	public:
		static void registerEvent(std::string event_name);
		static void triggerEvent(std::string event_name, EventData event_data);
		static void addHandler(std::string evet_name, handler_func*);

	private:
		static std::map<std::string, std::vector<handler_func*>> handlers;
	};

}