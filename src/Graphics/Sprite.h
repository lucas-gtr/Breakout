#pragma once

#include "math.h"

#include <string>

class Sprite {
protected:
  const vec2 m_size;
  
public:
  Sprite(const std::string& texture_path, const vec2& size) : m_size(size) { }
  const vec2& size() const { return m_size; }
    
  virtual ~Sprite() = default;
};
