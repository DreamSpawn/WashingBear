#include <WashingBear.h>
#include "../global.h"
#include "HexLayer.h"
#include <vector>

namespace WashingBear {

  std::vector<Layer*> layers;

  GLuint pick_frame_buffer = 0;
  GLuint pick_render_buffer = 0;

  static unsigned int CreateHexLayer(std::vector<WashingBear::Color4f> colors, unsigned int width) {
      HexLayer *new_hex_layer = new HexLayer(colors, width);
      new_hex_layer->setProjection(WashingBear::projection_x, WashingBear::projection_y);
      layers.push_back(new_hex_layer);
      return layers.size() -1;
  }

  static void SetHexes(unsigned int layer_id, std::vector<WashingBear::Hex> hexes) {
    Layer *layer = layers.at(layer_id);
    if (layer->getType() != HEX) return;
    dynamic_cast<HexLayer*>(layer)->setHexes(hexes);
  }

  static void SetSelected(unsigned int layer_id, unsigned int hex) {
    Layer* layer = layers.at(layer_id);
    if (layer->getType() != HEX) return;
    dynamic_cast<HexLayer*>(layer)->setSelected(hex);
  }

  static std::vector<int> PickGeom(int x, int y) {
    std::vector<int> hits = std::vector<int>(layers.size(), -1);

    GLint standard_frame_buffer;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &standard_frame_buffer);

    if (pick_frame_buffer == 0) {
      // Set up pick frame buffer
      glGenFramebuffers(1, &pick_frame_buffer);
      glBindFramebuffer(GL_FRAMEBUFFER, pick_frame_buffer);
      glGenRenderbuffers(1, &pick_render_buffer);
      glBindRenderbuffer(GL_RENDERBUFFER, pick_render_buffer);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, pick_render_buffer);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, window_width, window_height);
    } else {
      glBindFramebuffer(GL_FRAMEBUFFER, pick_frame_buffer);
    }

    for (int i = 0; i < layers.size(); i++) {
      hits.at(i) = layers.at(i)->pickGeom(x, y);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, standard_frame_buffer);
    return hits;
  }
}

