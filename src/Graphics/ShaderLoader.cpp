#include "ShaderLoader.hpp"

ShaderData ShaderLoader::Load(std::string shader_path) {
  ShaderData shader_data;
  
  std::ifstream stream(shader_path.c_str());
  if (!stream.is_open()) {
    std::cerr << "Failed to load shader: " << shader_path << '\n';
    return shader_data;
  }
  
  std::string line;
  ShaderLoader::ShaderType type = ShaderType::NONE;
  
  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    } else {
      if (type == ShaderType::VERTEX)
        shader_data.vertex_shader.append(line).append("\n");
      else if (type == ShaderType::FRAGMENT)
        shader_data.fragment_shader.append(line).append("\n");
    }
  }
  
  std::cout << "Shader from " << shader_path << " generated!" << '\n';
  return shader_data;
}
