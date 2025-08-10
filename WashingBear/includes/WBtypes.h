#pragma once


namespace WashingBear {
  enum LayerType {
    HEX
  };

  typedef struct {
    float r;
    float g;
    float b;
    float a;
  } Color4f;

  typedef struct {
    unsigned int color;
  } Hex;
}