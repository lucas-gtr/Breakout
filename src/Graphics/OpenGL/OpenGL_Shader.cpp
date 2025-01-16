#include "OpenGL_Shader.hpp"

OpenGL_Shader::OpenGL_Shader(const std::string& vertex_shader, const std::string& fragment_shader) {
  unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertex_shader.c_str());
  unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragment_shader.c_str());

  if (vertex && fragment) {
    LinkProgram(vertex, fragment);
  }
  
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  
  std::cout << "OpenGL shader (ID=" << m_ID << ") generated!" << '\n';
}

unsigned int OpenGL_Shader::CompileShader(GLenum type, const char* source) {
  unsigned int shader = glCreateShader(type);
  if (shader == 0) {
    std::string shader_type = (type == GL_VERTEX_ARRAY) ? "vertex" : "fragment";
    std::cerr << "Failed to create the " << type << " shader!" << std::endl;
    return 0;
  }
  
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);
  
  if(type == GL_VERTEX_SHADER){
    if(!CheckCompileErrors(shader, "VERTEX")) {
      glDeleteShader(shader);
      return 0;
    }
  } else if(type == GL_FRAGMENT_SHADER){
    if(!CheckCompileErrors(shader, "FRAGMENT")) {
      glDeleteShader(shader);
      return 0;
    }
  }
  
  return shader;
}

void OpenGL_Shader::LinkProgram(unsigned int vertex, unsigned int fragment) {
  m_ID = glCreateProgram();
  if (m_ID == 0) {
    std::cerr << "Failed to create the program shader!" << std::endl;
    return;
  }
  
  glAttachShader(m_ID, vertex);
  glAttachShader(m_ID, fragment);
  glLinkProgram(m_ID);
  
  if (!CheckCompileErrors(m_ID, "PROGRAM")) {
    glDeleteProgram(m_ID);
    m_ID = 0;
  }
}

bool OpenGL_Shader::CheckCompileErrors(unsigned int shader, const std::string& type) {
  int success;
  char infoLog[512];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, nullptr, infoLog);
      std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
      return false;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 512, nullptr, infoLog);
      std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      return false;
    }
  }
  
  return true;
}

OpenGL_Shader::~OpenGL_Shader() {
  glUseProgram(0);
  std::cout << "Deleting OpenGL shader (ID=" << m_ID << ")..." << '\n';
  glDeleteProgram(m_ID);
}

void OpenGL_Shader::Bind(){
  glUseProgram(m_ID);
}

void OpenGL_Shader::Unbind(){
  glUseProgram(0);
}

int OpenGL_Shader::GetUniformLocation(const std::string& name) {
  auto it = m_UniformLocationCache.find(name);
  if (it != m_UniformLocationCache.end())
    return it->second;
  
  int location = glGetUniformLocation(m_ID, name.c_str());
  
  if (location == -1) {
    std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
  }
  
  m_UniformLocationCache[name] = location;
  
  return location;
}

void OpenGL_Shader::SetUniform(const std::string &name, const bool value) {
  glUniform1i(GetUniformLocation(name), static_cast<int>(value));
}

void OpenGL_Shader::SetUniform(const std::string &name, const int value) {
  glUniform1i(GetUniformLocation(name), value);
}

void OpenGL_Shader::SetUniform(const std::string &name, const unsigned int value) {
  glUniform1ui(GetUniformLocation(name), value);
}

void OpenGL_Shader::SetUniform(const std::string &name, const float value) {
  glUniform1f(GetUniformLocation(name), value);
}

void OpenGL_Shader::SetUniform(const std::string &name, const int v0, const int v1) {
  glUniform2i(GetUniformLocation(name), v0, v1);
}

void OpenGL_Shader::SetUniform(const std::string &name, const unsigned int v0, const unsigned int v1) {
  glUniform2ui(GetUniformLocation(name), v0, v1);
}

void OpenGL_Shader::SetUniform(const std::string &name, const float v0, const float v1) {
  glUniform2f(GetUniformLocation(name), v0, v1);
}

void OpenGL_Shader::SetUniform(const std::string &name, const int v0, const int v1, const int v2) {
  glUniform3i(GetUniformLocation(name), v0, v1, v2);
}

void OpenGL_Shader::SetUniform(const std::string &name, const unsigned int v0, const unsigned int v1, const unsigned int v2) {
  glUniform3ui(GetUniformLocation(name), v0, v1, v2);
}

void OpenGL_Shader::SetUniform(const std::string &name, const float v0, const float v1, const float v2) {
  glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void OpenGL_Shader::SetUniform(const std::string &name, const int v0, const int v1, const int v2, const int v3) {
  glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
}

void OpenGL_Shader::SetUniform(const std::string &name, const unsigned int v0, const unsigned int v1, const unsigned int v2, const unsigned int v3) {
  glUniform4ui(GetUniformLocation(name), v0, v1, v2, v3);
}

void OpenGL_Shader::SetUniform(const std::string &name, const float v0, const float v1, const float v2, const float v3) {
  glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void OpenGL_Shader::SetUniform(const std::string &name, const vec2& vec) {
  glUniform2f(GetUniformLocation(name), vec[0], vec[1]);
}

void OpenGL_Shader::SetUniform(const std::string &name, const vec3& vec) {
  glUniform3f(GetUniformLocation(name), vec[0], vec[1], vec[2]);
}

void OpenGL_Shader::SetUniform(const std::string &name, const vec4& vec) {
  glUniform4f(GetUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
}

void OpenGL_Shader::SetUniform(const std::string &name, const mat3& matrix, GLboolean transpose){
  glUniformMatrix3fv(GetUniformLocation(name), 1, transpose, matrix);
}

void OpenGL_Shader::SetUniform(const std::string &name, const mat4& matrix, GLboolean transpose){
  glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, matrix);
}
