#include "../../include/Pieces/ConveyorBelt.h"


ConveyorBelt::ConveyorBelt(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 20.0f;
  float height = width*5;
  float points[] = {-width,-height, width,-height, width,height, -width,height};
  
  points_ = floatToPoints(points, 8);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
}


ConveyorBelt::ConveyorBelt(const ConveyorBelt& orig) {
}


ConveyorBelt::~ConveyorBelt() {
}