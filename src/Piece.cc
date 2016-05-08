#include "../include/Piece.h"

Piece::Piece() {
  static_ = false;
  dragged_ = false;
  pos_ = {900.0f, 200.0f};
  rotation_ = 0.0f;
  
  float width = 50.0f;
  float points[] = {-width,-width, width,-width, width,width, -width,width};
  
  points_ = floatToPoints(points, 8);
}


Piece::Piece(const Piece& orig) {
}


Piece::~Piece() {
}


void Piece::update() {
  if (!static_) {
    pos_.x = cpBodyGetPosition(physics_body_).x;
    pos_.y = cpBodyGetPosition(physics_body_).y;
  }
  
  if (dragged_) {
  
  }
}


void Piece::move() {
}


void Piece::draw() {
  ESAT::Mat3 translate;
  ESAT::Mat3InitAsTranslate(pos_.x, pos_.y, &translate);
  
  //Calculate transformed vertices
  float vertices_out[40];
  float vertex[2];
  float vertex_out[2];
  
  //Draw points
  int i;
  for (i=0; i<points_.size(); i++) {
    vertex[0] = points_[i].x;
    vertex[1] = points_[i].y;
    ESAT::Mat3TransformVec2(translate, vertex, vertex_out);
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
  cpShapeSetFriction(sbox, 1.0f);
  cpShapeSetMass(sbox, 0.5);
  
  cpVect position = {pos_.x, pos_.y};
  cpBodySetPosition(physics_body_, position);
}


void Piece::setStaticPhysics() {
  for(int i=0; i<points_.size(); i++) {
    
    MathLib::Point2 p1 = points_[i];
    MathLib::Point2 p2 = points_[i+1];
    
    cpShape* ground = cpSegmentShapeNew( cpSpaceGetStaticBody(space_), cpv(p1.x + pos_.x, p1.y + pos_.y), cpv(p2.x + pos_.x, p2.y + pos_.y), 2.0f);
    cpShapeSetFriction(ground, 1.0f);
    cpSpaceAddShape(space_, ground);
  }
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
  int click = false;
  float margin = 50.0f;
  
  //Check if clicked inside the button
  if (ESAT::MousePositionX() >= pos_.x
    && ESAT::MousePositionX() <= pos_.x + margin
    && ESAT::MousePositionY() >= pos_.y
    && ESAT::MousePositionY() <= pos_.y + margin) {
    click = 1;
  }
    
  return click;
}


/// @brief  An alias for CheckClick(), to be used for detecting hover
bool Piece::checkHover() {
  return checkClick();
}