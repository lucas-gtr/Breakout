#include "Renderer.hpp"

Renderer::Renderer(RenderingInterface* rendering_interface, int window_height, int window_width) : m_rendering_interface(rendering_interface), m_width(window_width), m_height(window_height) {
  float aspect_ratio = (float) window_height / window_width;
  m_proj_matrix = ortho(0.0, 1.0f, aspect_ratio, 0.0f, -1.0f, 1.0f);
  m_particle_generator = new ParticleGenerator(500);
}

void Renderer::DrawScene(float dt) {
  vec2 ball_position = m_rendering_interface->GetBallPosition();
  vec2 ball_radius = m_rendering_interface->GetBallSize() / 2.0f;
  vec2 ball_velocity = m_rendering_interface->GetBallVelocity();

  m_particle_generator->Update(dt, ball_position, ball_velocity, ball_radius);
  
  DrawSprite(m_background_sprite, vec2(0.0f));
  DrawSprite(m_platform_sprite, m_rendering_interface->GetPlatformPosition());
  DrawParticles(m_particle_sprite);
  DrawSprite(m_ball_sprite, ball_position);
  
  auto block_list = m_rendering_interface->GetBlockList();
  
  for(auto [pos, color_index] : block_list) {
    if(color_index == 0) DrawSprite(m_solid_block_sprite, pos, COLOR_LIST[color_index]);
    else DrawSprite(m_block_sprite, pos, COLOR_LIST[color_index]);
  }
}

Renderer::~Renderer() {  
  delete m_background_sprite;
  delete m_ball_sprite;
  delete m_platform_sprite;
  delete m_block_sprite;
  delete m_solid_block_sprite;
  delete m_particle_sprite;
  
  delete m_particle_generator;
}
