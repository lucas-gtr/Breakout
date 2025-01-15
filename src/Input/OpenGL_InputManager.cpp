#include "OpenGL_InputManager.hpp"

void OpenGL_InputManager::KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    m_input_interface->LaunchBall();
  
  if((action == GLFW_PRESS || action == GLFW_RELEASE)){
    if (key == GLFW_KEY_A) m_input_interface->SetMovingLeft(action == GLFW_PRESS);
    if (key == GLFW_KEY_D) m_input_interface->SetMovingRight(action == GLFW_PRESS);
  }
}
