#include "../../include/Pieces/Goal.h"


Goal::Goal(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  img_ = ESAT::SpriteFromFile("assets/img/goal.png");
  width_ = 100.0f;
  height_ = 100.0f;
  img_pivot_ = {-50.0f, -50.0f};
  
  movable_ = false;
}


Goal::Goal(const Goal& orig) {
}


Goal::~Goal() {
}

void Goal::setDynamicPhysics() {
  Piece::setDynamicPhysics();
}