#pragma once
#include "Layer.h"
#include <vector>

class HexLayer :
  public virtual Layer
{
public:
  HexLayer(std::vector<WashingBear::Color4f> colors, unsigned int width);

  void render();
  WashingBear::LayerType getType() { return WashingBear::HEX; }
  void setHexes(std::vector<WashingBear::Hex> hexes);
  void setSelected(unsigned int hex);
  void setProjection(float x, float y);
  void setTranlate(float x, float y);

  int pickGeom(int x, int y);

  ~HexLayer();

private:
  std::vector<WashingBear::Color4f> colors;
  std::vector<WashingBear::Hex> hexes;

  unsigned int width;

  unsigned int program;
  unsigned int color_buffer;
  int scaling_location;
  int pick_mode_location;
  int selected_location;
  int translate_location;
};

