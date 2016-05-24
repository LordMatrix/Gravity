#include "../../include/Pieces/Ball.h"


Ball::Ball(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 30.0f;
  float height = 30.0f;;
  float points[] = {-width,-height, width,-height, width,height, -width,height};
  
  points_ = floatToPoints(points, 8);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  img_ = ESAT::SpriteFromFile("assets/img/football.png");
  width_ = 60.0f;
  height_ = 60.0f;
  img_pivot_ = {-30.0f, -30.0f};
  
  movable_ = false;
}


Ball::Ball(const Ball& orig) {
}


Ball::~Ball() {
}

void Ball::setDynamicPhysics() {
  Piece::setDynamicPhysics();
  
  cpShapeSetMass(physics_shape_, 0.1f);
}