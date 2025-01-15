#include "GameLevel.hpp"

GameLevel::GameLevel(std::vector<std::vector<int>> level_grid, float y_max){
  std::cout << "Creating level..." << '\n';
  
  int rows = (int) level_grid.size();
  int cols = (int) level_grid[0].size();

  float block_x_size = 1.0f / cols;
  float block_y_size = (y_max / 2) / rows;
  vec2 block_size = vec2(block_x_size, block_y_size);
  
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      vec2 pos = vec2(j * block_x_size, i * block_y_size);
      int color_index = level_grid[i][j] - 1;
      if(color_index == 0) // Solid block
        m_block_list.emplace_back(new Block(pos, block_size, color_index, false));
      else if(color_index >= 1 && color_index <= 4) // Destructible block
        m_block_list.emplace_back(new Block(pos, block_size, color_index, true));
    }
  }
}

void GameLevel::Reset() {
  std::cout << "Level reset!" << '\n';
  for (const auto& block : m_block_list) block->Reset();
}

GameLevel::~GameLevel() {
  std::cout << "Deleting level..." << '\n';
}
