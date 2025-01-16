#pragma once

#include "GameObject.h"

class Ball : public GameObject {
private:
  vec2 m_velocity;
  
  const float m_radius;
  
public:
  Ball(const float radius);

  void Move(float delta_time);
  
  void SetPosition(const vec2& new_position);
  
  void SetVelocity(const vec2& new_velocity);
  void InvertVelocity(const int direction);
  const vec2& velocity() const;
  
  const float radius() const;
  
  ~Ball();
};
