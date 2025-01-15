#pragma once

#include "vector.h"
#include <vector>
#include <utility>

class InputInterface {
public:
  virtual void LaunchBall() = 0;
  virtual void SetMovingLeft(bool moving_left) = 0;
  virtual void SetMovingRight(bool moving_right) = 0;
};

