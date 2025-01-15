#pragma once

#include <vector>

#include "RenderingInterface.h"
#include "ShaderLoader.hpp"
#include "Sprite.h"

class Renderer {
private:
  const vec3 COLOR_LIST[5] = {
    vec3(0.8f, 0.8f, 0.7f), // Solid block
    vec3(0.2f, 0.6f, 1.0f),
    vec3(0.0f, 0.7f, 0.0f),
    vec3(0.8f, 0.8f, 0.4f),
    vec3(1.0f, 0.5f, 0.0f)
  };
  
  virtual void DrawSprite(Sprite* sprite, const vec2& position, const vec3& color = vec3(1.0f)) = 0;
  
protected:
  const std::string BALL_TEXTURE_PATH = "Assets/textures/awesomeface.png";
  const std::string PLATFORM_TEXTURE_PATH = "Assets/textures/paddle.png";
  const std::string BLOCK_TEXTURE_PATH = "Assets/textures/block.png";
  const std::string SOLID_BLOCK_TEXTURE_PATH = "Assets/textures/block_solid.png";
  const std::string BACKGROUND_TEXTURE_PATH = "Assets/textures/background.jpg";
  
  const std::string SPRITE_SHADER_PATH = "Assets/shaders/sprite.glsl";
  
  const int m_width, m_height;

  mat4 m_proj_matrix;
  
  RenderingInterface* m_rendering_interface;
    
  Sprite* m_ball_sprite;
  Sprite* m_platform_sprite;
  Sprite* m_block_sprite;
  Sprite* m_solid_block_sprite;
  Sprite* m_background_sprite;
  
  vec2 ToWindowCoord(const vec2& coord) const;
public:
  Renderer(RenderingInterface* rendering_interface, int window_height, int window_width);
  
  virtual bool InitializeWindow() = 0;
  virtual bool InitializeShader() = 0;
  virtual bool InitializeSprites() = 0;
  
  void DrawScene();
  virtual bool RenderScene() = 0;
  
  virtual void CleanScene() = 0;
  
};
