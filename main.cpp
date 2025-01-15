#include <iostream>
#include "src/Core/GameManager.hpp"
#include "src/Graphics/OpenGL/OpenGL_Rendering.hpp"
#include "src/Input/OpenGL_InputManager.hpp"

InputInterface* InputManager::m_input_interface = nullptr;

bool IsInteger(const std::string& str) {
  return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) { return std::isdigit(c); });
}

int main(int argc, const char * argv[]) {
  std::cout << "BREAKOUT GAME" << '\n';
  const int NUMBER_LEVEL = 4;
  
  int level;
  
  int width = 800;
  int height = 600;
  
  if (argc == 3) {
    std::string widthStr = argv[1];
    std::string heightStr = argv[2];
    if (IsInteger(widthStr) && IsInteger(heightStr)) {
      width = std::stoi(widthStr);
      height = std::stoi(heightStr);
    } else if(argc != 1) {
      std::cerr << "Error: Please provide either 0 or 2 parameters for window size." << std::endl;
      return 1;
    }
  }
    
  if(width < 400 || height < 400) {
    std::cerr << "Error: Window size must be at least 400x400." << std::endl;
    return 1;
  }
  
  const float aspect_ratio = (float)height / width;
  if (width > 2000 || height > 2000) {
    std::cerr << "Error: Window size must not exceed 2000x2000." << std::endl;
    return 1;
  }
  
  if (aspect_ratio < 0.5 || aspect_ratio > 2) {
    std::cerr << "Error: Aspect ratio must be between 0.5 and 2." << std::endl;
    return 1;
  }
  
  if(aspect_ratio < 0.5 || aspect_ratio > 2) {
    return 1;
  }

  while (true) {
    std::cout << "Enter the level you want to play (1-" << NUMBER_LEVEL << "): ";
    std::cin >> level;
    
    if (std::cin.fail()) {
      std::cout << "Invalid input. Please enter a number." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    
    if (level >= 1 && level <= 4) {
      break;
    } else {
      std::cout << "Invalid level. Please enter a number between 1 and "<< NUMBER_LEVEL << "." << std::endl;
    }
  }
  
  bool is_window_open = true;
  
  GameManager game = GameManager(aspect_ratio, NUMBER_LEVEL);
  game.SetCurrentLevel(level - 1);
  
  OpenGL_Rendering renderer(&game, height, width);
  OpenGL_InputManager::SetInputInterface(&game);
  
  if(!renderer.InitializeWindow()){
    renderer.CleanScene();
    return -1;
  }

  renderer.InitializeShader();
  renderer.InitializeSprites();

  while(is_window_open) {
    game.Update(0.016f);

    renderer.DrawScene();
    is_window_open = renderer.RenderScene();
  }

  renderer.CleanScene();
  return 0;
}
