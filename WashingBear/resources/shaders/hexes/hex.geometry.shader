#version 330 core

uniform vec2 projection;

layout(points) in;
layout(triangle_strip, max_vertices = 10) out;

in uint geom_color[];
//in vec2 geom_projection[];

flat out uint fragment_color;

void main() {
  fragment_color = geom_color[0];

  gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.5, 0.0, 0.0);
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position + vec4(0.433, 0.25, 0.0, 0.0);
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position;
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position + vec4(0.433, -0.25, 0.0, 0.0);
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position + vec4(0.0, -0.5, 0.0, 0.0);
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  EndPrimitive();

  gl_Position = gl_in[0].gl_Position + vec4(0.0, -0.5, 0.0, 0.0);
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position + vec4(-0.433, -0.25, 0.0, 0.0);
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position;
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position + vec4(-0.433, 0.25, 0.0, 0.0);
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  gl_Position = gl_in[0].gl_Position + vec4(0.0, 0.5, 0.0, 0.0);
  gl_Position.xy = gl_Position.xy * projection;
  EmitVertex();
  EndPrimitive();
}