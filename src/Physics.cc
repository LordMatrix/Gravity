#include "../include/Physics.h"

Physics::Physics() {
  simulation_running_ = false;
  simulation_started_ = false;
  ball_caged_ = false;
  space_ = nullptr;
}


Physics::Physics(const Physics& orig) {
  
}


Physics::~Physics() {
  
}
    

/************* PHYSICS CONTROL *************/
void Physics::deleteBody(cpBody *body, void *data) {
  cpSpaceRemoveBody(cpBodyGetSpace(body), body);
}


void Physics::deleteShape(cpShape *shape, void *data) {
  cpSpaceRemoveShape(cpShapeGetSpace(shape), shape);
  cpShapeFree(shape);
}


void Physics::deleteAllShapes(cpSpace *space, void *key, void *data) {
  if (!simulation_started_ && !simulation_running_) {
    cpSpaceEachShape(space, &Physics::deleteShape, NULL);
  }
}

void Physics::drawBody(cpBody *body, void *data) {

}


void Physics::drawShape(cpShape *shape, void *data) {
  ESAT::DrawSetStrokeColor(255,0,0,255);
  cpBB bb = cpShapeGetBB(shape);
  float path[] = {bb.l,bb.t, bb.r,bb.t, bb.r,bb.b, bb.l,bb.b, bb.l,bb.t};
  ESAT::DrawPath(path, 5);
}


/**
 * Prints all objects contained in the global space
 */
void Physics::drawPhysics() {
  cpSpaceEachBody(space_, drawBody, NULL);
  cpSpaceEachShape(space_, drawShape, NULL);
}
/*******************************************/


cpBool Physics::OnBallGoalCollisionEnter(cpArbiter *arb, cpSpace *space, void *data) {
  printf("You win\n");
  bool* caged = (bool*)data;
  *caged = true;
  return cpTrue;
}


cpBool Physics::OnBallConveyorCollisionEnter(cpArbiter *arb, cpSpace *space, void *data) {
  /*
  printf("You winHITHITHIT\n");
  cpShape *a = NULL;
  cpShape *b = NULL;
  cpBody *c = NULL;
  cpBody *d = NULL;
  
  cpArbiterGetShapes(arb, &a, &b);
  cpArbiterGetBodies(arb, &c, &d);
  
  cpBody* ball;
  
  
  if (cpShapeGetCollisionType(a) == BALL_TYPE) {
    ball = cpShapeGetBody(a);
  } else if (cpShapeGetCollisionType(b) == BALL_TYPE) {
    ball = cpShapeGetBody(b);
  }
  */
  
  cpBodyApplyForceAtLocalPoint(Manager::getInstance()->ball_->physics_body_ , cpVect{0.8f,0.0f}, cpVect{-10.0f,0.0f});
  return cpTrue;
}


cpBool Physics::OnBallSpringCollisionEnter(cpArbiter *arb, cpSpace *space, void *data) {
  
  cpBody* body = Manager::getInstance()->ball_->physics_body_;
  
  cpBodyApplyImpulseAtLocalPoint(body, cpVect{0.0f,-cpBodyGetVelocity(body).y}, cpVect{0.0f,-10.0f});
  return cpTrue;
}


void Physics::createCollisionHandlers() {
  //Create winning collision
  cpCollisionHandler* handler = cpSpaceAddCollisionHandler (space_, BALL_TYPE, GOAL_TYPE);
  handler->beginFunc = OnBallGoalCollisionEnter;
  handler->userData = &ball_caged_;
  
  handler = cpSpaceAddCollisionHandler (space_, BALL_TYPE, CONVEYORBELT_TYPE);
  handler->beginFunc = OnBallConveyorCollisionEnter;
  
  handler = cpSpaceAddCollisionHandler (space_, BALL_TYPE, SPRING_TYPE);
  handler->beginFunc = OnBallSpringCollisionEnter;
}



/************* SIMULATION CONTROL *************/

void Physics::startSimulation() {
  
  space_ = cpSpaceNew();
  cpSpaceSetGravity(space_, cpv(0, 0.0098f));
  
  simulation_running_ = true;
  simulation_started_ = true;
  
  createCollisionHandlers();
}


void Physics::pauseSimulation() {
  simulation_running_ = false;
}


void Physics::resumeSimulation() {
  simulation_running_ = true;
}


void Physics::stopSimulation() {
  simulation_started_ = false;
  simulation_running_ = false;
}