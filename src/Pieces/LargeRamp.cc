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
  
  id_ = 2;
  img_ = ESAT::SpriteFromFile("assets/img/ramp.png");
  width_ = 250.0f;
  height_ = 100.0f;
  img_pivot_ = {75.0f, 0.0f};
}


LargeRamp::LargeRamp(const LargeRamp& orig) {
}


LargeRamp::~LargeRamp() {
}


void LargeRamp::draw() {
  ESAT::Mat3 translate, rotate, scale, transform, sprmat;
  ESAT::Mat3InitAsTranslate(current_pos_.x, current_pos_.y, &translate);
  
  if (static_)
    ESAT::Mat3InitAsRotate(MathLib::rads(rotation_), &rotate);
  else 
    ESAT::Mat3InitAsRotate(rotation_, &rotate);
  
  ESAT::Mat3Multiply(translate, rotate, &transform);
  
  //Calculate transformed vertices
  float vertices_out[100];
  float vertex[2];
  float vertex_out[2];
  
  //Draw points
  int i;
  for (i=0; i<points_.size(); i++) {
    vertex[0] = points_[i].x;
    vertex[1] = points_[i].y;
    ESAT::Mat3TransformVec2(transform, vertex, vertex_out);
    vertices_out[2*i] = vertex_out[0];
    vertices_out[2*i+1] = vertex_out[1];
  }
  vertices_out[2*i] = vertices_out[0];
  vertices_out[2*i+1] = vertices_out[1];
    
  ESAT::DrawSetFillColor(0,200,200,200);
  ESAT::DrawSetStrokeColor(255,255,255,255);
  ESAT::DrawSolidPath(vertices_out, points_.size());

  if (img_ != nullptr) {
    
    float img_height = ESAT::SpriteHeight(img_);
    float img_width = ESAT::SpriteWidth(img_);
    
    float x_ratio = width_/img_width;
    float y_ratio = height_/img_height;
    
    ESAT::Mat3InitAsTranslate(current_pos_.x + img_pivot_.x, current_pos_.y + img_pivot_.y, &translate);
    //ESAT::Mat3InitAsTranslate(current_pos_.x,current_pos_.y, &translate);
    
    if (static_)
      ESAT::Mat3InitAsRotate(MathLib::rads(rotation_), &rotate);
    else 
      ESAT::Mat3InitAsRotate(rotation_, &rotate);
  
  
    ESAT::Mat3 center, centered;
    ESAT::Mat3InitAsTranslate(-width_/2, -height_/2, &center);
    ESAT::Mat3Multiply(rotate, center, &centered);
  
  
    ESAT::Mat3Multiply(translate, centered, &transform);
    
    ESAT::Mat3InitAsScale(x_ratio, y_ratio, &scale);
    ESAT::Mat3Multiply(transform, scale, &sprmat);
    
    ESAT::DrawSpriteWithMatrix(img_, sprmat);
  }
}