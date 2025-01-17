#pragma once

#include <vector>
#include <fstream>
#include <filesystem>

#include "../RenderingInterface.h"
#include "../InputInterface.h"

#include "GameObjects/Ball.hpp"
#include "GameObjects/Platform.hpp"
#include "GameLevel.hpp"

enum class GameState {
  HOLD, START
};

class GameManager : public RenderingInterface, public InputInterface {
private:
  const vec2 PLATFORM_SIZE = vec2(0.125f, 0.025f);
  const float PLATFORM_VELOCITY = 0.45f;
  
  const float BALL_VELOCITY = 0.5f;
  const vec2 BALL_DIRECTION = vec2(0.2f, -0.8f).unit();
  const float BALL_RADIUS = 0.015f;
  
  const float PLATFORM_ANGLE_FACTOR = 1.5f;
    
  const float m_y_max;
  
  const std::string LEVELS_PATH = "assets/levels/";
    
  GameState m_game_state = GameState::HOLD;

  Platform* m_platform;
  Ball* m_ball;
  bool m_is_ball_attached = true;
  
  bool m_moving_left = false;
  bool m_moving_right = false;
    
  std::vector<GameLevel*> m_level_list;
  int m_current_level = 0;

public:
  GameManager(const float aspect_ratio, const int number_level);
  
  // Rendering Interface
  const vec2& GetBallSize() const override { return m_ball->size(); }
  const vec2& GetPlatformSize() const override { return m_platform->size(); }
  const vec2& GetBlockSize() const override { return m_level_list[m_current_level]->GetBlockSize(); }
  
  const vec2& GetBallPosition() const override { return m_ball->position(); }
  const vec2 GetBallVelocity() const override { return (!m_is_ball_attached) ? m_ball->velocity() : vec2(0.0f); }
  const vec2& GetPlatformPosition() const override { return m_platform->position(); }
  const std::vector<std::pair<vec2, int>> GetBlockList() const override;
  
  // Input Interface
  void LaunchBall() override;
  void SetMovingLeft(bool moving_left) override;
  void SetMovingRight(bool moving_right) override;
  
  std::vector<std::vector<int>> ReadFileLevel(const std::string& file_path);
  void SetCurrentLevel(const int level) { m_current_level = level; }
  
  void Update(float delta_time);
  
  vec2 GetBallAttachedPosition() const;
  
  bool CheckCollisions(GameObject* other);
  
  void ResetGame();
  
  ~GameManager() override;
};
