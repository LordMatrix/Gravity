#include "../../include/Pieces/BowlingBall.h"


BowlingBall::BowlingBall(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  img_ = ESAT::SpriteFromFile("assets/img/bowling.png");
  width_ = 60.0f;
  height_ = 60.0f;
  img_pivot_ = {-30.0f, -30.0f};
  
  movable_ = true;
  
  points_.clear();
  MathLib::Vec2 position_offset = {0.0f, 0.0f};
  MathLib::assignRegularPolygon(20, 35, position_offset, 0.0f, points_);
}


BowlingBall::BowlingBall(const BowlingBall& orig) {
}


BowlingBall::~BowlingBall() {
}

void BowlingBall::setDynamicPhysics() {
  Piece::setDynamicPhysics();
  
  cpShapeSetMass(physics_shape_, 100.0f);
}