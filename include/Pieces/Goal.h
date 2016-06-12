/* Copyright 2016 Marcos Vazquez. All rights reserved.
 *
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>
 *
 * File:   Goal.h
 *
 */
//#ifndef WIN32
//#define WIN32 1
//#endif

#ifndef __GOAL_H__
#define __GOAL_H__ 1

#include <vector>
#include <cmath>
#include <ctgmath>
#include "../MathLib.h"
#include <ESAT/math.h>
#include <ESAT/time.h>
#include "ESAT_extra/chipmunk/chipmunk.h"
#include "../config.h"
#include "Piece.h"

class Goal: public Piece {
  public:
    Goal(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    Goal(const Goal& orig);
    virtual ~Goal();
    
    virtual void setDynamicPhysics() override;
      
  private:
};

#endif /* __GOAL_H__ */