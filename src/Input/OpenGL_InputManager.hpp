#pragma once

#include "InputManager.h"

#include <GLFW/glfw3.h>

class OpenGL_InputManager : public InputManager {
public:
  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
};
