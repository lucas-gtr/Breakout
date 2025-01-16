#include "GameManager.hpp"

GameManager::GameManager(const float aspect_ratio, const int number_level) : RenderingInterface(), m_y_max(aspect_ratio) {
  std::cout << "Game starting..." << '\n';
  m_platform = new Platform(PLATFORM_SIZE, m_y_max);
  
  m_ball = new Ball(BALL_RADIUS);
  m_ball->SetVelocity(BALL_DIRECTION * BALL_VELOCITY);
  
  for(int i = 1; i <= number_level; i++){
    std::vector<std::vector<int>> level = ReadFileLevel(LEVELS_PATH + std::to_string(i) + ".lvl");
    m_level_list.emplace_back(new GameLevel(level, m_y_max));
  }
  
  m_game_state = GameState::START;
}


std::vector<std::vector<int>> GameManager::ReadFileLevel(const std::string& file_path) {
  std::vector<std::vector<int>> level_grid;

  std::ifstream file(file_path);
  if(!file.is_open()) {
    std::cerr << "Couldn't open the file: " << file_path << '\n';
    std::exit(EXIT_FAILURE);
  }
  
  std::string line;
  while (getline(file, line)) {
    std::vector<int> row;
    for(int x = 0; x < line.size(); x+=2) row.push_back(line[x] - '0');
    if(row.size() > 0) level_grid.push_back(row);
  }
  
  return level_grid;
}

const std::vector<std::pair<vec2, int>> GameManager::GetBlockList() const {
  std::vector<std::pair<vec2, int>> block_list;
  for (auto block_ptr : m_level_list[m_current_level]->block_list()) {
    if(!block_ptr->IsDestroyed())
      block_list.push_back(std::make_pair(block_ptr->position(), block_ptr->color()));
  }
  return block_list;
}

vec2 GameManager::GetBallAttachedPosition() const {
  vec2 ball_position = m_platform->position();
  ball_position.x += (PLATFORM_SIZE.x / 2) - BALL_RADIUS;
  ball_position.y -= 2*BALL_RADIUS;
  
  return ball_position;
}

void GameManager::Update(float delta_time) {
  if(m_game_state == GameState::HOLD) return;
  
  if(m_moving_left) m_platform->Move(-PLATFORM_VELOCITY * delta_time);
  if(m_moving_right) m_platform->Move(PLATFORM_VELOCITY * delta_time);
  
  if(!m_is_ball_attached) m_ball->Move(delta_time);
  else {
    m_ball->SetPosition(GetBallAttachedPosition());
    return;
  }
  if(m_ball->position().y >= m_y_max) {
    ResetGame();
    return;
  }
  
  if(m_ball->position().y <= 0.0f) {
    m_ball->InvertVelocity(1);
    m_ball->SetPosition(vec2(m_ball->position().x, 0.0f));
  }
  
  if(m_ball->position().x + m_ball->size().x >= 1.0f || m_ball->position().x <= 0.0f) {
    m_ball->InvertVelocity(0);
    vec2 new_pos = m_ball->position();
    if(m_ball->position().x <= 0.0f)
      new_pos.x = 0.0f;
    else
      new_pos.x = 1.0f - 2*m_ball->radius();
    m_ball->SetPosition(new_pos);
  }
  
  if(CheckCollisions(m_platform)) {
    double platform_percentage = -0.5 + (m_ball->position().x + m_ball->radius()
                                - (m_platform->position().x)) / (m_platform->size().x);
    
    vec2 new_direction(sin(platform_percentage * PLATFORM_ANGLE_FACTOR),
                       -abs(cos(platform_percentage * PLATFORM_ANGLE_FACTOR)));
    
    m_ball->SetVelocity(new_direction * BALL_VELOCITY);
    return;
  }
  
  for(auto block : m_level_list[m_current_level]->block_list()){
    if(!block->IsDestroyed() && CheckCollisions(block)) {
      block->Destroy();
      return;
    }
  }
}

void GameManager::LaunchBall() {
  if(!m_is_ball_attached) return;
  
  m_is_ball_attached = false;
}

void GameManager::SetMovingLeft(bool moving_left){
  m_moving_left = moving_left;
}

void GameManager::SetMovingRight(bool moving_right){
  m_moving_right = moving_right;
}

bool GameManager::CheckCollisions(GameObject* other){
  vec2 ball_center = m_ball->position() + m_ball->radius();
  vec2 half_block_size = other->size() / 2.0f;
  
  vec2 block_center(other->position() + half_block_size);
  
  vec2 block_border_position = ball_center - block_center;
  block_border_position.clamp(-half_block_size, half_block_size);
  
  vec2 distance_ball_border = ball_center - (block_border_position + block_center);
  
  auto BounceBall = [&](int i) {
    vec2 new_pos = m_ball->position();
    m_ball->InvertVelocity(i);
    if(block_border_position[i] < 0)
      new_pos[i] -= distance_ball_border[i] + m_ball->radius();
    else
      new_pos[i] -= distance_ball_border[i] - m_ball->radius();
    m_ball->SetPosition(new_pos);
  };
  
  if (distance_ball_border.length() <= m_ball->radius()) {
    if(abs(block_border_position.y) == half_block_size.y || dynamic_cast<Platform*>(other)) {
      BounceBall(1);
    }
    else if(abs(block_border_position.x) == half_block_size.x) {
      BounceBall(0);
    }
    
    return true;
  }
  else return false;
}
     


void GameManager::ResetGame() {
  m_level_list[m_current_level]->Reset();
  m_platform->Reset();
  m_is_ball_attached = true;
  m_ball->SetPosition(GetBallAttachedPosition());
}

GameManager::~GameManager() {
  for(const auto& level : m_level_list) delete level;
  delete m_ball;
  delete m_platform;
  
  std::cout << "Game finished!" << '\n';
}
