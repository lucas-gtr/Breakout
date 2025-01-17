#pragma once

#include <string>
#include <iostream>

struct TextureData {
  unsigned char* image;
  int width;
  int height;
  int n_channels;
};

class TextureLoader {
public:
  static TextureData Load(std::string texture_path);
};
