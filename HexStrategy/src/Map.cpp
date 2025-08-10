#include "Map.h"
#include <fstream>

constexpr unsigned int MAP_VERSION = 1;

struct TerrainDetails {
  WashingBear::Color4f color;
  unsigned int flags;
};

TerrainDetails terrain_details[] = {
  { // OCEAN_DEEP
    {0.0f, 0.0f, 0.5f, 1.0f},
    0
  },
  { // OCEAN
    {0.0f, 0.0f, 1.0f, 1.0f},
    0
  },
  { // OCEAN_SHALLOW,
    {0.1f, 0.6f, 0.8f, 1.0f},
    0
  },
  { // LAKE
    {0.2f, 0.6f, 1.0f, 1.0f},
    0
  },
  { // DESSERT
    {1.0f, 1.0f, 0.5f, 1.0f},
    0
  },
  { // TUNDRA
    {0.8f, 0.8f, 0.8f, 1.0f},
    0
  },
  { // SAVANNAH
    {0.0f, 0.0f, 0.5f, 1.0f},
    0
  },
  { // MEADOW
    {0.1f, 0.8f, 0.0f, 1.0f},
    0
  },
  { // THICKET
    {0.0f, 0.0f, 0.5f, 1.0f},
    0
  },
  { // FOREST
    {0.0f, 0.0f, 0.5f, 1.0f},
    0
  },
  { // HILLS
    {0.0f, 0.0f, 0.5f, 1.0f},
    0
  },
  { // MOUNTAIN
    {0.0f, 0.0f, 0.5f, 1.0f},
    0
  },
};

Map::Map(unsigned int width) : width{width} {}

std::vector<WashingBear::Color4f> Map::terrain_colors() {
  std::vector<WashingBear::Color4f> colors = std::vector<WashingBear::Color4f>(TERRAIN_TOTAL_COUNT);
  for (int i = 0; i < TERRAIN_TOTAL_COUNT; i++) {
    colors.at(i) = terrain_details[i].color;
  }
  return colors;
}

Map Map::load(std::string file_name) {
  std::cout << "Loading map from file: " << file_name << std::endl;

  std::ifstream map_file(file_name, std::ios::binary);
  if (!map_file.is_open()) {
    std::cout << "Failed to open file" << std::endl;
    return Map(0);
  }

  unsigned int map_version;
  map_file.read((char*)&map_version, sizeof map_version);
  if (map_version != MAP_VERSION) {
    std::cout << "Unknown map version: " << map_version << std::endl;
    return Map(0);
  }

  unsigned int width;
  map_file.read((char*)&width, sizeof width);

  Map new_map = Map(width);

  unsigned int height;
  map_file.read((char*)&height, sizeof height);

  unsigned char *tiles = new unsigned char[width * height];
  map_file.read((char*)tiles, width * height);

  map_file.close();

  new_map.tiles.assign((Tile*)tiles, (Tile*)tiles + width * height);
  delete[] tiles;

  return new_map;
}

std::vector<WashingBear::Hex> Map::getHexes() {
  std::vector<WashingBear::Hex> hexes = std::vector<WashingBear::Hex>(tiles.size());
  for (int i = 0; i < tiles.size(); i++) {
    hexes.at(i).color = tiles[i].terrain;
  }
  return hexes;
}

Map::~Map() {
  tiles.~vector();
}