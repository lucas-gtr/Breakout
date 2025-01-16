#include "OpenGL_Sprite.hpp"

OpenGL_Sprite::OpenGL_Sprite(const std::string& texture_path, const vec2& size) : Sprite(texture_path, size) {
  
  TextureData texture_data = TextureLoader::Load(texture_path);
  m_texture = new OpenGL_Texture(texture_data.image, texture_data.width,
                                 texture_data.height, texture_data.n_channels);

  unsigned int VBO;
  float vertices[] = {
    // pos      // tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };
  
  glGenVertexArrays(1, &this->m_VAO);
  glGenBuffers(1, &VBO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glBindVertexArray(this->m_VAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glDeleteBuffers(1, &VBO);
  
  std::cout << "OpenGL VAO (ID=" << m_VAO << ") generated!" << '\n';
}

OpenGL_Sprite::~OpenGL_Sprite() {
  delete m_texture;
  glBindVertexArray(0);
  std::cout << "Deleting OpenGL VAO (ID=" << m_VAO << ")..." << '\n';
  glDeleteVertexArrays(1, &m_VAO);
}
