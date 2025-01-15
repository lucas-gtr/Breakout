#include "Platform.hpp"

Platform::Platform(const vec2& size, float y_max) : GameObject(vec2(0.5f - (size[0] / 2), y_max - (size[1] * 1.5f)), size){
  std::cout << "Creating platform..." << '\n';
}

void Platform::Move(float x_move){
  if(m_position[0] + x_move > 0.0f && m_position[0] + x_move + m_size[0] < 1.0f)
    m_position[0] += x_move;
}

void Platform::Reset(){
  std::cout << "Reseting platform..." << '\n';
  m_position[0] = 0.5f;
}

Platform::~Platform() {
  std::cout << "Deleting platform..." << '\n';
}
