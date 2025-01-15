#pragma once

#include "GameObject.h"

class Platform : public GameObject {
public:
  Platform(const vec2& size, float y_max);
  
  void Move(float x_move);
  void Reset();
  
  ~Platform();
};
