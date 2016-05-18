#include "../../include/Pieces/SmallRamp.h"


SmallRamp::SmallRamp(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 50.0f;
  float points[] = {-width,-width, width,width, -width,width};
  
  points_ = floatToPoints(points, 6);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  img_ = ESAT::SpriteFromFile("assets/img/ramp.png");
  width_ = 100.0f;
  height_ = 100.0f;
  img_pivot_ = {-50.0f, -50.0f};
}


SmallRamp::SmallRamp(const SmallRamp& orig) {
}


SmallRamp::~SmallRamp() {
}