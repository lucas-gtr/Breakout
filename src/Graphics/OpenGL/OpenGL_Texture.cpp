#include "OpenGL_Texture.hpp"

OpenGL_Texture::OpenGL_Texture(unsigned char* image, int width, int height, int n_channels) {
  glGenTextures(1, &m_ID);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_ID);

  GLenum texture_format = GL_RGBA;
  if(n_channels == 3) texture_format = GL_RGB;
  
  glTexImage2D(GL_TEXTURE_2D, 0, texture_format, width, height, 0, texture_format, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  std::cout << "OpenGL texture (ID=" << m_ID << ") generated!" << '\n';

  glBindTexture(GL_TEXTURE_2D, 0);
}

OpenGL_Texture::~OpenGL_Texture() {
  glBindTexture(GL_TEXTURE_2D, 0);
  std::cout << "Deleting OpenGL texture (ID=" << m_ID << ")..." << '\n';
  glDeleteTextures(1, &m_ID);
}
