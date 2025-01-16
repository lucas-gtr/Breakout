#pragma once

#include "../InputInterface.h"

class InputManager {
protected:
  static InputInterface* m_input_interface;
  
public:
  static void SetInputInterface(InputInterface* input_interface) { m_input_interface = input_interface; }
};
