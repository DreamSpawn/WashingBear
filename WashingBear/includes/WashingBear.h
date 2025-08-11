#pragma once
#include "WBtypes.h"
#include "EventManager.h"
#include <string>
#include <vector>

#ifdef WB_ENGINE
#define WB_API __declspec(dllexport)
#else
#define WB_API __declspec(dllimport)
#endif // WB_ENGINE

namespace WashingBear {

  WB_API void SetTitle(std::string title);
  WB_API void SetResourcePath(std::string path);
  WB_API int InitGLWindow();
  WB_API int Run();
  
  WB_API unsigned int CreateHexLayer(std::vector<WashingBear::Color4f> colors, unsigned int width);
  WB_API void SetHexes(unsigned int layer, std::vector<WashingBear::Hex> hexes);

  WB_API std::vector<int> PickGeom();
}