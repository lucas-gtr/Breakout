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
}
