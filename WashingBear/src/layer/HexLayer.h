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
  void setProjection(float x, float y);

  void setHexes(std::vector<WashingBear::Hex> hexes);
  void addHex(unsigned int position, unsigned int color);
  unsigned int addColor(float red, float green, float blue);

  ~HexLayer();

private:
  std::vector<WashingBear::Color4f> colors;
  std::vector<WashingBear::Hex> hexes;

  unsigned int color_buffer;
  unsigned int program;
  unsigned int width;
};

