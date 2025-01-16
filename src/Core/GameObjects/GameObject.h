#pragma once

#include "geometry.h"
#include <string>

class GameObject {  
protected:
  vec2 m_position;
  vec2 m_size;

  GameObject(const vec2& position, const vec2& size) : m_position(position), m_size(size) { }
  
public:
  const vec2& position() const { return m_position; }
  const vec2& size() const { return m_size; }

  virtual ~GameObject() = default;
};
