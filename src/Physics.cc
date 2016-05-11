#include "../include/Physics.h"

Physics::Physics() {
  simulation_running_ = false;
  simulation_started_ = false;
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
  return cpTrue;
}

  
void Physics::createCollisionHandlers() {
  //Create winning collision
  cpCollisionHandler* handler = cpSpaceAddCollisionHandler (space_, BALL_TYPE, GOAL_TYPE);
  handler->beginFunc = OnBallGoalCollisionEnter;
//  handler->userData = g_colliders;
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