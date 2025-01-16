#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../Renderer.hpp"
#include "OpenGL_Sprite.hpp"
#include "OpenGL_Shader.hpp"
#include "../../Input/OpenGL_InputManager.hpp"

class OpenGL_Rendering : public Renderer {
private:
  const std::string SPRITE_SHADER_PATH = "src/Graphics/OpenGL/shaders/sprite.glsl";
  const std::string PARTICLE_SHADER_PATH = "src/Graphics/OpenGL/shaders/particle.glsl";

  GLFWwindow* m_window;
  
  OpenGL_Shader* m_sprite_shader;
  OpenGL_Shader* m_particle_shader;
  
  void DrawSprite(Sprite* sprite, const vec2& position, const vec3& color = vec3(1.0f)) override;
  void DrawParticles(Sprite* sprite) override;

public:
  OpenGL_Rendering(RenderingInterface* rendering_interface, int window_height, int window_width);
  
  bool InitializeWindow() override;
  bool InitializeShader() override;
  bool InitializeSprites() override;
  
  bool RenderScene() override;
  void CleanScene() override;
  
  ~OpenGL_Rendering();
};
