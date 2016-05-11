/* Copyright 2015 Marcos Vazquez. All rights reserved.    
 * 
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>  
 * Created on November 23, 2015, 1:22 AM
 *
 * File:   Misc.h                                              
 * A static class holding common functions
 *
 */
//#ifndef WIN32
//#define WIN32 1
//#endif

#ifndef PHYSICS_H
#define PHYSICS_H 1

#include "stdio.h"

#include "ESAT/draw.h"
#include "ESAT/input.h"
#include "ESAT_extra/chipmunk/chipmunk.h" 

#include "config.h"


class Physics {
  
  public:

    Physics();
    Physics(const Physics& orig);
    ~Physics();
    
    //Delete
    static void deleteBody(cpBody *body, void *data);
    static void deleteShape(cpShape *shape, void *data);
    void deleteAllShapes(cpSpace *space, void *key, void *data);
    
    //Draw
    static void drawBody(cpBody *body, void *data);
    static void drawShape(cpShape *shape, void *data);
    void drawPhysics();

    //Collisions
    static cpBool OnBallGoalCollisionEnter(cpArbiter *arb, cpSpace *space, void *data);    
    void createCollisionHandlers();
    
    //Simulation Flow
    void startSimulation();
    void pauseSimulation();
    void resumeSimulation();
    void stopSimulation();
    
    
    //Flags
    bool simulation_running_;
    bool simulation_started_;
    cpSpace* space_;
};

#endif /* PHYSICS_H */