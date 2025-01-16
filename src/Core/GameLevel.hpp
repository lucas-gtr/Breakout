#pragma once

#include <vector>

#include "GameObjects/Block.h"

class GameLevel {
private:
  std::vector<Block*> m_block_list;
  
public:
  GameLevel(std::vector<std::vector<int>> level_grid, float y_max);
  
  void Reset();
  const vec2& GetBlockSize() const { return m_block_list[0]->size(); };
  const std::vector<Block*>& block_list() const { return m_block_list; }
  
  ~GameLevel();
};
