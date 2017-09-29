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
  
  id_ = 6;
  img_ = MOMOS::SpriteFromFile("src/Gravity/assets/img/conveyor.png");
  width_ = 40.0f;
  height_ = 200.0f;
  
  if (collision_type == CONVEYORBELT_TYPE) {
    rotation_ = -90.0f;
    img_pivot_ = {-100.0f, 20.0f};
  } else {
    rotation_ = 90.0f;
    img_pivot_ = {100.0f, -20.0f};
  }
  
  colspan_ = 2;
}


ConveyorBelt::ConveyorBelt(const ConveyorBelt& orig) {
}


ConveyorBelt::~ConveyorBelt() {
}