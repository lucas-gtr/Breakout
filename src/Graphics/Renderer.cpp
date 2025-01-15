#include "Renderer.hpp"

Renderer::Renderer(RenderingInterface* rendering_interface, int window_height, int window_width) : m_rendering_interface(rendering_interface), m_width(window_width), m_height(window_height) {
  float aspect_ratio = (float) window_height / window_width;
  m_proj_matrix = ortho(0.0, 1.0f, aspect_ratio, 0.0f, -1.0f, 1.0f);
}

void Renderer::DrawScene() {
  DrawSprite(m_background_sprite, vec2(0.0f));
  DrawSprite(m_platform_sprite, m_rendering_interface->GetPlatformPosition());
  DrawSprite(m_ball_sprite, m_rendering_interface->GetBallPosition());
  
  auto block_list = m_rendering_interface->GetBlockList();
  
  for(auto [pos, color_index] : block_list) {
    if(color_index == 0) DrawSprite(m_solid_block_sprite, pos, COLOR_LIST[color_index]);
    else DrawSprite(m_block_sprite, pos, COLOR_LIST[color_index]);
  }
}
