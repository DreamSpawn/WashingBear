#pragma once
#include <string>
#include <map>

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

  typedef struct {
    std::map<std::string, double> numbers;
    std::map<std::string, std::string> text;
  } EventData;
}