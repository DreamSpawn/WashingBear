#pragma once
#include <iostream>
#include <vector>
#include "WBtypes.h"

enum terrain_type : unsigned char {
  OCEAN_DEEP,
  OCEAN,
  OCEAN_SHALLOW,
  LAKE,
  DESSERT,
  TUNDRA,
  SAVANNAH,
  MEADOW,
  THICKET,
  FOREST,
  HILLS,
  MOUNTAIN,
  TERRAIN_TOTAL_COUNT
};

typedef struct {
  terrain_type terrain;
} Tile;

class Map {
  public:
    Map(unsigned int width);
    ~Map();

    Map static load(std::string file_name);

    unsigned int get_width() { return width; };
    std::vector<WashingBear::Color4f> static terrain_colors();
    std::vector<WashingBear::Hex> getHexes();

  private:
    std::vector<Tile> tiles;

    unsigned int width;
};