#include <WashingBear.h>
#include "../global.h"
#include "HexLayer.h"
#include <vector>

namespace WashingBear {

  std::vector<Layer*> layers;

  static unsigned int CreateHexLayer(std::vector<WashingBear::Color4f> colors, unsigned int width) {
      HexLayer *new_hex_layer = new HexLayer(colors, width);
      new_hex_layer->setProjection(WashingBear::projection_x, WashingBear::projection_y);
      layers.push_back(new_hex_layer);
      return layers.size();
  }

  static void SetHexes(unsigned int layer_id, std::vector<WashingBear::Hex> hexes) {
    Layer *layer = layers.at(layer_id-1);
    if (layer->getType() != HEX) return;
    dynamic_cast<HexLayer*>(layer)->setHexes(hexes);
  }

  static std::vector<int> PickGeom() {
    std::vector<int> hits = std::vector<int>(layers.size(), -1);
    for (int i = 0; i < layers.size(); i++) {
      hits.at(i) = layers.at(i)->pickGeom();
    }
    return hits;
  }
}

