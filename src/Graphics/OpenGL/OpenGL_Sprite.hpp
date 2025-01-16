#pragma once

#include <GL/glew.h>

#include "../Sprite.h"
#include "../TextureLoader.hpp"

#include "OpenGL_Texture.hpp"

class OpenGL_Sprite : public Sprite {
private:
  unsigned int m_VAO;
  OpenGL_Texture* m_texture;
  
public:
  OpenGL_Sprite(const std::string& texture_path, const vec2& size);
  
  const unsigned int texture() const { return m_texture->ID(); }
  const unsigned int VAO() const { return m_VAO; }

  ~OpenGL_Sprite();
};
