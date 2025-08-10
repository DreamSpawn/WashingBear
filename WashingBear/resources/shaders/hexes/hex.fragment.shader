#version 330 core

uniform vec4[{color_count}] colors;

flat in uint fragment_color;

layout(location = 0) out vec4 color;

void main() {
  color = colors[fragment_color];
}