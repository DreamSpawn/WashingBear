#include "WashingBear.h"
#include "Map.h"
#include "GUI.h"

unsigned int hex_layer;

int main() {
	WashingBear::SetTitle("HexStrategy");
	WashingBear::SetResourcePath("../WashingBear/resources");

	int width = 1200;
	int height = 800;

	if (WashingBear::InitGLWindow(width, height) == -1) {
		return -1;
	}

	Map world = Map::load("../HexStrategy/resources/maps/test.map");
	hex_layer = WashingBear::CreateHexLayer(Map::terrain_colors(), world.get_width());
	WashingBear::SetHexes(hex_layer, world.getHexes());

	initGUI(width, height);

	return WashingBear::Run();
}