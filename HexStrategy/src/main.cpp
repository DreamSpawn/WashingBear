#include "WashingBear.h"
#include "Map.h"
#include "GUI.h"

unsigned int hex_layer;

int main() {
	WashingBear::SetTitle("HexStrategy");
	WashingBear::SetResourcePath("../WashingBear/resources");

	if (WashingBear::InitGLWindow() == -1) {
		return -1;
	}

	Map world = Map::load("../HexStrategy/resources/maps/test.map");
	hex_layer = WashingBear::CreateHexLayer(Map::terrain_colors(), world.get_width());
	WashingBear::SetHexes(hex_layer, world.getHexes());

	initGUI();

	return WashingBear::Run();
}