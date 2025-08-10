#include "HexLayer.h"
#include "../global.h"
#include <GL/glew.h>
#include "../shaders.h"
#include <memory>

extern std::string WashingBear::resourcePath;

HexLayer::HexLayer(std::vector<WashingBear::Color4f> colors, unsigned int width) : colors{colors}, width{width} {
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
  int pos_location = glGetUniformLocation(program, "pos");

  glUseProgram(program);
  glUniform4fv(colors_location, colors.size(), (float*) colors.data());
  glUniform1ui(width_location, width);
  glUniform2ui(pos_location, 5u, 5u);
}

void HexLayer::setProjection(float x, float y) {
  int pos_projection = glGetUniformLocation(program, "projection");
  glUniform2f(pos_projection, x, y);
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
}

void HexLayer::addHex(unsigned int position, unsigned int color) {

}

unsigned int HexLayer::addColor(float red, float green, float blue) {
  return 0;
}

HexLayer::~HexLayer() {
  colors.~vector();
  hexes.~vector();
}