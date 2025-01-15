#include "OpenGL_Rendering.hpp"

OpenGL_Rendering::OpenGL_Rendering(RenderingInterface* rendering_interface, int window_height, int window_width) : Renderer(rendering_interface, window_height, window_width) { }

bool OpenGL_Rendering::InitializeWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_RESIZABLE, true);
  
  m_window = glfwCreateWindow(m_width, m_height, "Breakout", nullptr, nullptr);
  if(!m_window) {
    std::cerr << "Failed to initialize the window" << '\n';
    return false;
  }
  
  glfwMakeContextCurrent(m_window);
  
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << '\n';
    return false;
  }
  
  glfwSetKeyCallback(m_window, OpenGL_InputManager::KeyCallback);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  std::cout << "Window created!" << '\n';
  return true;
}

bool OpenGL_Rendering::InitializeShader() {
  ShaderData shader_data = ShaderLoader::Load(SPRITE_SHADER_PATH);
  m_shader = new OpenGL_Shader(shader_data.vertex_shader, shader_data.fragment_shader);
  
  m_shader->Bind();
  m_shader->SetUniform("projection", m_proj_matrix);

  return true;
}

bool OpenGL_Rendering::InitializeSprites() {
  m_background_sprite = new OpenGL_Sprite(BACKGROUND_TEXTURE_PATH, vec2(1.0f));
  m_ball_sprite = new OpenGL_Sprite(BALL_TEXTURE_PATH, m_rendering_interface->GetBallSize());
  m_platform_sprite = new OpenGL_Sprite(PLATFORM_TEXTURE_PATH, m_rendering_interface->GetPlatformSize());
  m_block_sprite = new OpenGL_Sprite(BLOCK_TEXTURE_PATH, m_rendering_interface->GetBlockSize());
  m_solid_block_sprite = new OpenGL_Sprite(SOLID_BLOCK_TEXTURE_PATH, m_rendering_interface->GetBlockSize());

  return true;
}

bool OpenGL_Rendering::RenderScene() {
  glfwPollEvents();
  glfwSwapBuffers(m_window);
  
  glClear(GL_COLOR_BUFFER_BIT);
  
  if(glfwWindowShouldClose(m_window)){
    return false;
  }
  return true;
}

void OpenGL_Rendering::DrawSprite(Sprite* sprite, const vec2& position, const vec3& color){
  OpenGL_Sprite* openGL_sprite = dynamic_cast<OpenGL_Sprite*>(sprite);
  
  vec2 pos = position;
  vec2 size = sprite->size();
  
  mat4 model = mat4(1.0f);
  model.translate(vec3(pos, 0.0f));
  model.scale(size);
        
  m_shader->SetUniform("model", model);
  m_shader->SetUniform("spriteColor", color);
  m_shader->SetUniform("image", 0);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, openGL_sprite->texture());
  
  glBindVertexArray(openGL_sprite->VAO());
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);  
}

void OpenGL_Rendering::CleanScene() {
  std::cout << "Deleting the window..." << '\n';
  glfwDestroyWindow(m_window);
  glfwTerminate();
}
