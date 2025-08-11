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
  void setProjection(float x, float y);

  int pickGeom();

  ~HexLayer();

private:
  std::vector<WashingBear::Color4f> colors;
  std::vector<WashingBear::Hex> hexes;

  unsigned int color_buffer;
  unsigned int program;
  unsigned int width;
};

