#include "../../include/Pieces/SeeSaw.h"


SeeSaw::SeeSaw(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 100.0f;
  float height = 20.0f;;
  float points[] = {-width,-height, width,-height, width,height, -width,height};
  
  points_ = floatToPoints(points, 8);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  img_ = ESAT::SpriteFromFile("assets/img/lever0.png");
  width_ = 200.0f;
  height_ = 40.0f;
  img_pivot_ = {-30.0f, -30.0f};
  
  movable_ = false;
}


SeeSaw::SeeSaw(const SeeSaw& orig) {
}


SeeSaw::~SeeSaw() {
}

void SeeSaw::setDynamicPhysics() {
  Piece::setDynamicPhysics();
 
  cpVect position = cpVect{current_pos_.x, current_pos_.y};
  cpVect pivot_pos = cpVect{-1000.0f, 0.0f};
  
  cpBody* pivot = cpBodyNewStatic();
  cpSpaceAddBody(space_, pivot);
  cpBodySetPosition(pivot, pivot_pos);
  cpShape* sbox = cpSpaceAddShape(space_, cpBoxShapeNew(pivot, 1, 1, 1));
  
  cpPivotJoint* pin = cpPivotJointAlloc();
  pin = cpPivotJointInit(pin, physics_body_, pivot, position, position);
  cpConstraint* c = cpPivotJointNew(physics_body_, pivot, position);
  cpSpaceAddConstraint(space_, c);

}