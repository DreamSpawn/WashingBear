#version 330 core

uniform uint width;
uniform vec2 translate;
uniform bool pick_mode;
uniform uint selected_id;

layout(location = 0) in uint color_id;

out uint geom_color;
out int is_selected;

void main() {
  is_selected = 0;  

  if (pick_mode) {
    geom_color = uint(gl_VertexID);
  } else {
    if (selected_id == uint(gl_VertexID)) {
      is_selected = 1;
    }    
    geom_color = color_id;
  }

  uint i = uint(gl_VertexID);
  uint y = i / width;
  uint x = i % width;

  float scale = 5.0;
  
  gl_Position = vec4(0.866 * x + 0.433 * ( y % 2u ), -0.75 * y, 0.0, scale);
  gl_Position.xy += translate * scale;
}