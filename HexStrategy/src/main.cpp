#include "WashingBear.h"
#include "Map.h"

int main() {
	WashingBear::SetTitle("HexStrategy");
	WashingBear::SetResourcePath("../WashingBear/resources");

	if (WashingBear::InitGLWindow() == -1) {
		return -1;
	}

	Map world = Map::load("../HexStrategy/resources/maps/test.map");
	unsigned int hex_layer = WashingBear::CreateHexLayer(Map::terrain_colors(), world.get_width());
	WashingBear::SetHexes(hex_layer, world.getHexes());

	return WashingBear::Run();
}