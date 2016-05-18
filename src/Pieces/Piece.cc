#include "../../include/Pieces/Piece.h"

Piece::Piece() {
  static_ = false;
  dragged_ = false;
  initial_pos_ = {0.0f, 0.0f};
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  rotation_ = 0.0f;
  active_ = false;
  colspan_ = 1;
  movable_ = true;
  
  physics_body_ = nullptr;
  physics_shape_ = nullptr;
  collision_type_ = 0;
  
  float width = 50.0f;
  float points[] = {-width,-width, width,-width, width,width, -width,width};
  
  points_ = floatToPoints(points, 8);
}


Piece::Piece(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space) : Piece(){
  
  space_ = space;
  initial_pos_ = initial_pos;
  set_pos_ = initial_pos_;
  current_pos_ = initial_pos_;
  static_ = is_static;
  collision_type_ = collision_type;
}


Piece::Piece(const Piece& orig) {
}


Piece::~Piece() {
}


void Piece::update() {
  if (active_ && !static_) {
    current_pos_.x = cpBodyGetPosition(physics_body_).x;
    current_pos_.y = cpBodyGetPosition(physics_body_).y;
    
    rotation_ = cpBodyGetAngle(physics_body_);
  }
  
  if (dragged_) {
  
  }
}


void Piece::move() {
}


void Piece::draw() {
  ESAT::Mat3 translate, rotate, transform;
  ESAT::Mat3InitAsTranslate(current_pos_.x, current_pos_.y, &translate);
  ESAT::Mat3InitAsRotate(MathLib::rads(rotation_), &rotate);
  
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
}


void Piece::setPhysics() {
  if (static_) {
    //Remove existing physics
    for (int i=physics_segments_.size()-1; i>=0; i--) {
      if (physics_segments_[i] != nullptr) {
        cpSpaceRemoveShape(space_, physics_segments_[i]);
        physics_segments_.pop_back();
      }
    }
    physics_segments_.clear();
    
    //Set new physics
    setStaticPhysics();
  } else {
    setDynamicPhysics();
  }
  
}


void Piece::setDynamicPhysics() {
  physics_body_ = cpSpaceAddBody(space_, cpBodyNew(0,0));
  cpShape* sbox = cpSpaceAddShape(space_, cpBoxShapeNew(physics_body_, 20, 20, 3));
  physics_shape_ = sbox;
  
  cpPolyShape* poly =  cpPolyShapeAlloc();
  cpTransform transform = cpTransformNew(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  cpVect verts[500];
  
  for (int i=0; i<points_.size(); i++) {
    verts[i] = cpVect {0.0f, 0.0f};
    verts[i].x = points_[i].x;
    verts[i].y = points_[i].y;
  }
  cpPolyShapeInit(poly, physics_body_, points_.size(), verts, transform, 1.0f);
  
  cpShapeSetElasticity(sbox, 0);
  cpShapeSetFriction(sbox, 0.4f);
  cpShapeSetMass(sbox, 0.5);
  
  cpVect position = {current_pos_.x, current_pos_.y};
  cpBodySetPosition(physics_body_, position);
  
  cpBodySetAngle(physics_body_, rotation_);
  
  cpShapeSetCollisionType(physics_shape_, collision_type_);
}


void Piece::setStaticPhysics() {
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
  }
  
  //Remove garbage
  points_.pop_back();
}


std::vector<MathLib::Point2> Piece::floatToPoints(float* arr, int length) {
  std::vector<MathLib::Point2> points;
  
  for (int i=0; i<length; i+=2) {
    MathLib::Point2 point = {arr[i], arr[i+1]};
    points.push_back(point);
  }
  
  return points;
}


float* Piece::pointsToFloat(std::vector<MathLib::Point2> points) {
  float* arr = (float*)malloc(points.size()*2 * sizeof(float));
  
  for (int i=0; i<points.size(); i++) {
    arr[2*i] = points[i].x;
    arr[2*i+1] = points[i].y;
  }
  
  return arr;
}


/// @brief  Checks and returns if the piece has been clicked
bool Piece::checkClick() {
  int i, j = 0;
  int click = false;
  float margin = 5.0f;
  
  int num_vertices = points_.size();
  float mx = ESAT::MousePositionX();
  float my = ESAT::MousePositionY();
  
  
  //Raycast the area
  for (i = 0, j = num_vertices - 1; i < num_vertices; j = i++) {
    MathLib::Point2 p1, p2;
    p1.x = points_[i].x + current_pos_.x + margin;
    p1.y = points_[i].y + current_pos_.y - margin;
    p2.x = points_[j].x + current_pos_.x + margin;
    p2.y = points_[j].y + current_pos_.y - margin;
    
    
    if (((p1.y > my) != (p2.y > my)) &&
        (mx < (p2.x - p1.x) * (my - p1.y) / (p2.y - p1.y) + p1.x))
          click = !click;
  }
  
  return click;
}


/// @brief  An alias for CheckClick(), to be used for detecting hover
bool Piece::checkHover() {
  return checkClick();
}


void Piece::drop() {
  set_pos_ = {(float)ESAT::MousePositionX(), (float)ESAT::MousePositionY()};
  current_pos_ = set_pos_;
}