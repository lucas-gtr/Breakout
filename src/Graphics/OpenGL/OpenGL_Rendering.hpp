#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.hpp"
#include "OpenGL_Sprite.hpp"
#include "OpenGL_Shader.hpp"
#include "../../Input/OpenGL_InputManager.hpp"

class OpenGL_Rendering : public Renderer {
private:
  GLFWwindow* m_window;
  
  OpenGL_Shader* m_shader;
  void DrawSprite(Sprite* sprite, const vec2& position, const vec3& color = vec3(1.0f)) override;

public:
  OpenGL_Rendering(RenderingInterface* rendering_interface, int window_height, int window_width);
  
  bool InitializeWindow() override;
  bool InitializeShader() override;
  bool InitializeSprites() override;
  
  bool RenderScene() override;
  void CleanScene() override;
};
