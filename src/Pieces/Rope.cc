#include "../../include/Pieces/Rope.h"


Rope::Rope(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 5.0f;
  float height = 10.0f;;
  float points[] = {-width,-height, width,-height, width,height, -width,height};
  
  //points_ = floatToPoints(points, 8);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  id_ = 10;
  img_ = ESAT::SpriteFromFile("assets/img/ring.png");
  width_ = 10.0f;
  height_ = 20.0f;
  img_pivot_ = {-15.0f, -5.0f};
  
  movable_ = false;
  
  num_segments_ = 10;
  
  for (int i=0; i<num_segments_; i++) {
    current_poss_.push_back(new MathLib::Vec2());
  }
}


Rope::Rope(const Rope& orig) {
}


Rope::~Rope() {
}

void Rope::setDynamicPhysics() {
  
  physics_shapes_.clear();
  physics_bodies_.clear();
  
  //Create a static body
  cpVect pivot_pos = {current_pos_.x, current_pos_.y};
  cpBody* pivot = cpBodyNewStatic();
  cpSpaceAddBody(space_, pivot);
  cpBodySetPosition(pivot, pivot_pos);
  cpShape* sbox = cpSpaceAddShape(space_, cpBoxShapeNew(pivot, 1, 1, 1));
  sbox = cpSpaceAddShape(space_, cpBoxShapeNew(pivot, 1, 1, 1));
  
  cpBody* previous_segment = pivot;
  cpVect previous_position = pivot_pos; 
  
  physics_shapes_.push_back(sbox);
  physics_bodies_.push_back(pivot);
  
  for (int i=0; i<num_segments_; i++) {
    
    cpBody* newbody = cpSpaceAddBody(space_, cpBodyNew(0,0));
    cpShape* sbox = cpSpaceAddShape(space_, cpBoxShapeNew(newbody, width_, height_, 3));
    
    
    cpVect verts[5];
    
    //CREATE ROPE SEGMENT 
    verts[0] = cpVect {0.0f, 0.0f};
    verts[1] = cpVect {20.0f, 0.0f};
    verts[2] = cpVect {20.0f, 20.0f};
    verts[3] = cpVect {0.0f, 20.0f};
      
    for (int j=0; j<4; j++) {
      MathLib::Point2* point = (MathLib::Point2*) malloc(sizeof(MathLib::Point2));
      points_.push_back(point);
      points_[j]->x = verts[j].x;
      points_[j]->y = verts[j].y;
    }
    
    
    cpShapeSetElasticity(sbox, 0.0001f);
    cpShapeSetFriction(sbox, 0.0001f);
    
    float mass = 0.0001f / ((i+1)*10000000*(i+1));
    cpShapeSetMass(sbox, mass);
    
    cpVect position = {current_pos_.x, 30 + current_pos_.y + i*30};
    cpBodySetPosition(newbody, position);
    
    cpSlideJoint* pin = cpSlideJointAlloc();
    pin = cpSlideJointInit(pin, newbody, previous_segment, position, previous_position,0,0);
    cpConstraint* c = cpPivotJointNew(newbody, previous_segment, previous_position);
    cpSpaceAddConstraint(space_, c);
    
    previous_segment = newbody;
    previous_position = position;
    
    physics_shapes_.push_back(sbox);
    physics_bodies_.push_back(newbody);
  }
}

  
void Rope::update() {
  if (active_ && !static_) {
    for (int i=0; i<num_segments_; i++) {
      current_poss_[i]->x = cpBodyGetPosition(physics_bodies_[i]).x;
      current_poss_[i]->y = cpBodyGetPosition(physics_bodies_[i]).y;

      rotation_ = 0.0f;
    }
  }
}


void Rope::draw() {
  
  for (int j=0; j<num_segments_; j++) {
    
    ESAT::Mat3 translate, rotate, scale, transform, sprmat;
    ESAT::Mat3InitAsTranslate(current_poss_[j]->x, current_poss_[j]->y, &translate);

    if (img_ != nullptr) {

      float img_height = ESAT::SpriteHeight(img_);
      float img_width = ESAT::SpriteWidth(img_);

      //Make this overflow its bounding box
      float overflow = 2.5f;
      float x_ratio = (width_/img_width) * overflow;
      float y_ratio = height_/img_height * overflow;

      ESAT::Mat3InitAsTranslate(current_poss_[j]->x, current_poss_[j]->y, &translate);

      if (static_)
        ESAT::Mat3InitAsRotate(MathLib::rads(rotation_), &rotate);
      else 
        ESAT::Mat3InitAsRotate(rotation_, &rotate);


      ESAT::Mat3 center, centered;
      ESAT::Mat3InitAsTranslate(-width_, -height_, &center);
      ESAT::Mat3Multiply(rotate, center, &centered);


      ESAT::Mat3Multiply(translate, centered, &transform);

      ESAT::Mat3InitAsScale(x_ratio, y_ratio, &scale);
      ESAT::Mat3Multiply(transform, scale, &sprmat);

      ESAT::DrawSpriteWithMatrix(img_, sprmat);
    }
  }
}