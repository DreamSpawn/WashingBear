#include "HexLayer.h"
#include "../global.h"
#include <GL/glew.h>
#include "../shaders.h"
#include <memory>
#include <iostream>

extern std::string WashingBear::resourcePath;

HexLayer::HexLayer(std::vector<WashingBear::Color4f> colors, unsigned int width) : colors{colors}, width{width} {
  color_buffer = 0;

  std::string vertex_source = WashingBear::LoadShaderFile(WashingBear::resourcePath + "/shaders/hexes/hex.vertex.shader");
  std::string geometry_source = WashingBear::LoadShaderFile(WashingBear::resourcePath + "/shaders/hexes/hex.geometry.shader");
  std::string fragment_source = WashingBear::LoadShaderFile(WashingBear::resourcePath + "/shaders/hexes/hex.fragment.shader");

  // Set color count in fragment shader
  size_t start_pos = fragment_source.find("{color_count}");
  fragment_source.replace(start_pos, (size_t) 13, std::to_string( (int) colors.size()));

  program = WashingBear::CreateShader(
    geometry_source,
    vertex_source,
    fragment_source
  );
  
  int colors_location = glGetUniformLocation(program, "colors");
  int width_location = glGetUniformLocation(program, "width");
  scaling_location = glGetUniformLocation(program, "scaling");
  translate_location = glGetUniformLocation(program, "translate");
  pick_mode_location = glGetUniformLocation(program, "pick_mode");
  selected_location = glGetUniformLocation(program, "selected_id");

  glUseProgram(program);
  glUniform4fv(colors_location, colors.size(), (float*) colors.data());
  glUniform1ui(width_location, width);
  glUniform2f(scaling_location, 1.0, 1.0);
  glUniform2f(translate_location, 0.0, 0.0);
  glUniform1i(pick_mode_location, 0);
}

void HexLayer::setProjection(float x, float y) {
  glUniform2f(scaling_location, x, y);
}

void HexLayer::setTranlate(float x, float y) {
  glUniform2f(translate_location, x, y);
}

void HexLayer::render() {
  if (hexes.size() == 0) return;

  glUseProgram(program);
  glDrawArrays(GL_POINTS, 0, hexes.size());
}

void HexLayer::setHexes(std::vector<WashingBear::Hex> hexes_in) {
  hexes = hexes_in;
  int hexcount = hexes.size();
  unsigned int *color_content = new unsigned int[hexcount];
  for (int i = 0; i < hexcount; i++) {
    color_content[i] = hexes.at(i).color;
  }

  glGenBuffers(1, &color_buffer);

  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glBufferData(GL_ARRAY_BUFFER, hexcount * sizeof(unsigned int), color_content, GL_STATIC_DRAW);
  delete[] color_content;

  glEnableVertexAttribArray(0);
  glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, 0, 0);

  float height = (float) hexes.size() / width;
  glUniform2f(translate_location, width * -.0866, height * 0.075);
}

void HexLayer::setSelected(unsigned int hex) {
  glUniform1ui(selected_location, hex);
}

int HexLayer::pickGeom(int x, int y) {
  if (hexes.size() == 0) return -1;

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program);
  glUniform1i(pick_mode_location, 1);
  glDrawArrays(GL_POINTS, 0, hexes.size());
  glUniform1i(pick_mode_location, 0);

  unsigned int id;
  glReadPixels(x, WashingBear::window_height - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &id);

  return id;
}

HexLayer::~HexLayer() {
  colors.~vector();
  hexes.~vector();
}