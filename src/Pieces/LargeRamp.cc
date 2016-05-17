#include "../../include/Pieces/LargeRamp.h"


LargeRamp::LargeRamp(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 50.0f;
  float points[] = {-width,-width, width*4,width, -width,width};
  
  points_ = floatToPoints(points, 6);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  colspan_ = 2;
}


LargeRamp::LargeRamp(const LargeRamp& orig) {
}


LargeRamp::~LargeRamp() {
}