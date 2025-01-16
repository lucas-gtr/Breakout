#include "ParticleGenerator.hpp"

ParticleGenerator::ParticleGenerator(const int particle_count) : m_particle_count(particle_count){
  
  for (unsigned int i = 0; i < particle_count; ++i)
    m_particle_list.push_back(Particle());
}

void ParticleGenerator::Update(float dt, const vec2& ball_position, const vec2& ball_velocity, const vec2& offset) {
  for (unsigned int i = 0; i < PARTICLE_PER_FRAME; ++i)
  {
    int unused_particle = FirstUnusedParticle();
    RespawnParticle(m_particle_list[unused_particle], ball_position, ball_velocity, offset);
  }
  for (unsigned int i = 0; i < m_particle_count; ++i)
  {
    Particle& p = m_particle_list[i];
    p.life -= dt;
    if (p.life > 0.0f)
    {
      p.position -= p.velocity * dt;
      p.color.w -= dt * 2.5f;
    }
  }
}

void ParticleGenerator::RespawnParticle(Particle &particle, const vec2& ball_position, const vec2& ball_velocity, const vec2& offset)
{
  float random = ((rand() % 100) - 50) / 20000.0f;
  float r_color = 0.5f + ((rand() % 100) / 100.0f);
    
  particle.position = ball_position + (offset / 2.0) + random;
  particle.color = vec4(r_color, r_color, r_color, 1.0f);
  particle.life = 1.0f;
  particle.velocity = ball_velocity * 0.1f;
}

unsigned int ParticleGenerator::FirstUnusedParticle()
{
  for (unsigned int i = m_last_used_particle; i < m_particle_count; ++i) {
    if (m_particle_list[i].life <= 0.0f){
      m_last_used_particle = i;
      return i;
    }
  }
  
  for (unsigned int i = 0; i < m_last_used_particle; ++i) {
    if (m_particle_list[i].life <= 0.0f){
      m_last_used_particle = i;
      return i;
    }
  }
  m_last_used_particle = 0;
  return 0;
}

const std::vector<Particle>& ParticleGenerator::particle_list() const {
  return m_particle_list;
}



