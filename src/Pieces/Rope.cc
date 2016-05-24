#include "../../include/Pieces/Rope.h"


Rope::Rope(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 5.0f;
  float height = 10.0f;;
  float points[] = {-width,-height, width,-height, width,height, -width,height};
  
  points_ = floatToPoints(points, 8);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  img_ = ESAT::SpriteFromFile("assets/img/wall.png");
  width_ = 10.0f;
  height_ = 20.0f;
  img_pivot_ = {-15.0f, -5.0f};
  
  movable_ = false;
}


Rope::Rope(const Rope& orig) {
}


Rope::~Rope() {
}

void Rope::setDynamicPhysics() {
  int num_segments = 10;
  
  Piece::setDynamicPhysics();
  
  
  //Create a static body
  cpVect pivot_pos = cpVect{0.0f, -1000.0f};
  cpBody* pivot = cpBodyNewStatic();
  cpSpaceAddBody(space_, pivot);
  cpBodySetPosition(pivot, pivot_pos);
  cpShape* sbox = cpSpaceAddShape(space_, cpBoxShapeNew(pivot, 1, 1, 1));
  
  
  //Create dynamic shapes joined together
  cpVect position = cpVect{current_pos_.x, current_pos_.y};
  
  
  //Attach 1st shape to the static body
  
  
  
  
 
  
  
  cpPivotJoint* pin = cpPivotJointAlloc();
  pin = cpPivotJointInit(pin, physics_body_, pivot, position, position);
  cpConstraint* c = cpPivotJointNew(physics_body_, pivot, position);
  cpSpaceAddConstraint(space_, c);

}