#pragma once
#include "WBtypes.h"
#include "Events.h"
#include <string>
#include <vector>

#ifdef WB_ENGINE
#define WB_API __declspec(dllexport)
#else
#define WB_API __declspec(dllimport)
#endif // WB_ENGINE

namespace WashingBear {

  // Engine
  WB_API void SetTitle(std::string title);
  WB_API void SetResourcePath(std::string path);
  WB_API int InitGLWindow();
  WB_API int Run();
  
  // LayerManager
  WB_API unsigned int CreateHexLayer(std::vector<WashingBear::Color4f> colors, unsigned int width);
  WB_API void SetHexes(unsigned int layer, std::vector<WashingBear::Hex> hexes);
  WB_API void SetSelected(unsigned int layer, unsigned int hex);

  WB_API std::vector<int> PickGeom(int x, int y);
}