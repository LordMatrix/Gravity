#include "../../include/Pieces/SmallRamp.h"


SmallRamp::SmallRamp(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 50.0f;
  float points[] = {-width,-width, 0,0, width,width, -width,width};
  
  points_ = floatToPoints(points, 8);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
}


SmallRamp::SmallRamp(const SmallRamp& orig) {
}


SmallRamp::~SmallRamp() {
}