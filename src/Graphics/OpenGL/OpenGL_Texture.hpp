#pragma once

#include <GL/glew.h>

class OpenGL_Texture {
private:
  unsigned int m_ID;
  
public:
  OpenGL_Texture(unsigned char* image, int width, int height, int n_channels);
  const int ID() const { return m_ID; };
};
