#include "Ball.hpp"

Ball::Ball(const float radius) : GameObject(vec2(0.0f), vec2(radius * 2)), m_velocity(vec2(0.0f)), m_radius(radius) {
  std::cout << "Creating ball..." << '\n';
}

void Ball::Move(float delta_time) {
  m_position += m_velocity * delta_time;
}

void Ball::SetPosition(const vec2& new_position){
  m_position = new_position;
}

void Ball::SetVelocity(const vec2& new_velocity) {
  m_velocity = new_velocity;
}

void Ball::InvertVelocity(const int direction) {
  m_velocity[direction] *= -1;
}

vec2 Ball::velocity() const {
  return m_velocity;
}

const float Ball::radius() const {
  return m_radius;
}

Ball::~Ball() {
  std::cout << "Deleting ball..." << '\n';
}
