#pragma once

#include "GameObject.h"

class Block : public GameObject {
private:
  const int m_color;

  const bool m_is_destructible;
  bool m_destroyed = false;

public:
  Block(const vec2& position, const vec2& size, const int color_index, const bool is_destructible)
  : GameObject(position, size), m_color(color_index), m_is_destructible(is_destructible) { }
  
  const int color() const { return m_color; }

  void Reset() { m_destroyed = false; }
  
  void Destroy() {
    if(m_is_destructible)
      m_destroyed = true;
  }
  const bool IsDestroyed() const { return m_destroyed; }
};
