#include "../../include/Pieces/Spring.h"


Spring::Spring(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 50.0f;
  float height = 30.0f;;
  float points[] = {-width,-height, width,-height, width,height, -width,height};
  
  points_ = floatToPoints(points, 8);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  id_ = 4;
  img_ = ESAT::SpriteFromFile("assets/img/spring.png");
  width_ = 100.0f;
  height_ = 60.0f;
  img_pivot_ = {-50.0f, -30.0f};
}


Spring::Spring(const Spring& orig) {
}


Spring::~Spring() {
}