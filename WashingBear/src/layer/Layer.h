#pragma once
#include <WBtypes.h>

class Layer
{
public:
  virtual void render() = 0;
  virtual WashingBear::LayerType getType() = 0;
  virtual void setProjection(float x, float y) = 0;
  virtual void setTranlate(float x, float y) = 0;
  virtual int pickGeom(int x, int y) = 0 ;
  virtual ~Layer() {}
};

