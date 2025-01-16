#pragma once

#include "vector.h"
#include <vector>

class RenderingInterface {
public:
  virtual const vec2& GetBallPosition() const = 0;
  virtual const vec2& GetBallSize() const = 0;
  virtual const vec2 GetBallVelocity() const = 0;
  
  virtual const vec2& GetPlatformPosition() const = 0;
  virtual const vec2& GetPlatformSize() const = 0;
  
  virtual const vec2& GetBlockSize() const = 0;
  
  virtual const std::vector<std::pair<vec2, int>> GetBlockList() const = 0;
  
  virtual ~RenderingInterface() = default;
};
