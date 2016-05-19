#include "../../include/Pieces/Bouncer.h"


Bouncer::Bouncer(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  //Redefine shape
  float width = 50.0f;
  float height = 50.0f;;
  float points[] = {-width,-height, width,-height, width,height, -width,height};
  
  points_ = floatToPoints(points, 8);
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
  
  img_ = ESAT::SpriteFromFile("assets/img/bouncer.png");
  width_ = 100.0f;
  height_ = 100.0f;
  img_pivot_ = {-50.0f, -50.0f};
}


Bouncer::Bouncer(const Bouncer& orig) {
}


Bouncer::~Bouncer() {
}

void Bouncer::setStaticPhysics() {
  ESAT::Mat3 translate, rotate, transform;
  MathLib::Point2 p1, p2;
  
  //Momentarily add points
  points_.push_back(points_[0]);
  
  for(int i=0; i<points_.size()-1; i++) {
    
    p1 = points_[i];
    p2 = points_[i+1];

    ESAT::Mat3 translate, rotate, transform;
    ESAT::Mat3InitAsTranslate(current_pos_.x, current_pos_.y, &translate);
    ESAT::Mat3InitAsRotate(MathLib::rads(rotation_), &rotate);
    ESAT::Mat3Multiply(translate, rotate, &transform);

    std::vector<MathLib::Point2> f;  
    f.push_back(p1);
    f.push_back(p2);
    
    float vertices_out[100];
    float vertex[2];
    float vertex_out[2];

    //Draw points
    int j;
    for (j=0; j<f.size(); j++) {
      vertex[0] = f[j].x;
      vertex[1] = f[j].y;
      ESAT::Mat3TransformVec2(transform, vertex, vertex_out);
      vertices_out[2*j] = vertex_out[0];
      vertices_out[2*j+1] = vertex_out[1];
    }
    vertices_out[2*j] = vertices_out[0];
    vertices_out[2*j+1] = vertices_out[1];
   
    physics_segments_.push_back(cpSegmentShapeNew( cpSpaceGetStaticBody(space_), cpv(vertices_out[0], vertices_out[1]), cpv(vertices_out[2], vertices_out[3]), 2.0f));
    cpShapeSetFriction(physics_segments_[i], 1.0f);
    cpSpaceAddShape(space_, physics_segments_[i]);
    
    cpShapeSetCollisionType(physics_segments_[i], collision_type_);
    cpShapeSetElasticity(physics_segments_[i], 30.0f);
  }
  
  //Remove garbage
  points_.pop_back();
}