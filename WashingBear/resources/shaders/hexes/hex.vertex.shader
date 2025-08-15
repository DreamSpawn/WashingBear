#version 330 core

uniform uint width;
uniform uvec2 pos;
uniform bool pick_mode;
uniform uint selected_id;

layout(location = 0) in uint color_id;

out uint geom_color;

void main() {
  if (pick_mode) {
    geom_color = uint(gl_VertexID);
  } else {
    if (selected_id == uint(gl_VertexID)) {
      geom_color = 1U;
    } else {
      geom_color = color_id;
    }
  }
  uint i = uint(gl_VertexID);
  uint y = i / width;
  uint x = i % width;
  
  gl_Position = vec4(0.866 * x + 0.433 * ( y % 2u ), -0.75 * y, 0.0, 5.0);
  gl_Position = gl_Position - vec4(0.866 * pos.x, -0.75 * pos.y, 0.0, 0.0);
}