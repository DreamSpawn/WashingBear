#version 330 core

uniform uint width;
uniform uvec2 pos;
//uniform vec2 projection;

layout(location = 0) in uint color_id;

out uint geom_color;
//out vec2 geom_projection;

void main() {
  geom_color = color_id;
  //geom_projection = projection;
  uint i = uint(gl_VertexID);
  uint y = i / width;
  uint x = i % width;
  
  gl_Position = vec4(0.866 * x + 0.433 * ( y % 2u ), -0.75 * y, 0.0, 5.0);
  gl_Position = gl_Position - vec4(0.866 * pos.x, -0.75 * pos.y, 0.0, 0.0);
  //gl_Position.x = gl_Position.x * projection.x;
  //gl_Position.y = gl_Position.y * projection.y;
}