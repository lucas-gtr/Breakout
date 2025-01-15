#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include <string>

#include "matrix.h"

class OpenGL_Shader {
private:
  unsigned int m_ID;
  
  std::unordered_map<std::string, int> m_UniformLocationCache;

  unsigned int CompileShader(GLenum type, const char* source);
  void LinkProgram(unsigned int vertex, unsigned int fragment);
  bool CheckCompileErrors(unsigned int shader, const std::string& type);
  
  int GetUniformLocation(const std::string& name);
  
public:
  OpenGL_Shader(const std::string& vertex_shader, const std::string& fragment_shader);
  
  const int ID() const { return m_ID; };
  
  ~OpenGL_Shader();
  
  void Bind();
  void Unbind();
  
  void SetUniform(const std::string &name, const bool value);
  void SetUniform(const std::string &name, const int value);
  void SetUniform(const std::string &name, const unsigned int value);
  void SetUniform(const std::string &name, const float value);
  
  void SetUniform(const std::string &name, const int v0, const int v1);
  void SetUniform(const std::string &name, const unsigned int v0, const unsigned int v1);
  void SetUniform(const std::string &name, const float v0, const float v1);
  
  void SetUniform(const std::string &name, const int v0, const int v1, const int v2);
  void SetUniform(const std::string &name, const unsigned int v0, const unsigned int v1,
                  const unsigned int v2);
  void SetUniform(const std::string &name, const float v0, const float v1, const float v2);
  
  void SetUniform(const std::string &name, const int v0, const int v1, const int v2, const int v3);
  void SetUniform(const std::string &name, const unsigned int v0, const unsigned int v1,
                  const unsigned int v2, const unsigned int v3);
  void SetUniform(const std::string &name, const float v0, const float v1, const float v2, const float v3);
  
  void SetUniform(const std::string &name, const vec3& vec);
  void SetUniform(const std::string &name, const vec4& vec);
  
  void SetUniform(const std::string &name, const mat3& matrix, GLboolean transpose = GL_TRUE);
  void SetUniform(const std::string &name, const mat4& matrix, GLboolean transpose = GL_TRUE);
};
