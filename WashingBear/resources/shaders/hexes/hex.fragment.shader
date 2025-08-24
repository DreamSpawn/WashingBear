#version 330 core

uniform vec4[{color_count}] colors;
uniform bool pick_mode;

flat in uint fragment_color;
flat in int highlight;

layout(location = 0) out vec4 color;

void main() {
  if (pick_mode) {
    uint r = fragment_color % 256U;
    uint g = (fragment_color/256U) % 256U;
    uint b = (fragment_color/65536U) % 256U;
    color = vec4( float(r)/255.0, float(g)/255.0, float(b)/255.0, 0.0);
  } else {
    color = colors[fragment_color];

    if (highlight == 1) {
      color = color * 0.8 + vec4(0.0, 1.0, 0.0, 1.0) * 0.2;
    }    
  }
}
