#pragma once

#include <string>
#include <iostream>
#include <fstream>

struct ShaderData {
  std::string vertex_shader;
  std::string fragment_shader;
};

class ShaderLoader {
public:
  enum ShaderType{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };  
  static ShaderData Load(std::string shader_path);
};
