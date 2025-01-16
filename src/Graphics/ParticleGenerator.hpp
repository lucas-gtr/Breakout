#pragma once

#include "vector.h"
#include <vector>

struct Particle {
  vec2 position, velocity;
  vec4 color;
  float life;
  
  Particle()
  : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
};

class ParticleGenerator {
private:
  const unsigned int PARTICLE_PER_FRAME = 4;

  const unsigned int m_particle_count;
  std::vector<Particle> m_particle_list;
  
  unsigned int m_last_used_particle;
  
public:
  ParticleGenerator(int particle_count);
  
  void Update(float dt, const vec2& ball_position, const vec2& ball_velocity, const vec2& offset);
  
  unsigned int FirstUnusedParticle();
  void RespawnParticle(Particle& particle, const vec2& ball_position, const vec2& ball_velocity, const vec2& offset);
  
  const std::vector<Particle>& particle_list() const;
  
};
