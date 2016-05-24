/* Copyright 2016 Marcos Vazquez. All rights reserved.
 *
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>
 *
 * File:   Ball.h
 *
 */
//#ifndef WIN32
//#define WIN32 1
//#endif

#ifndef __BALL_H__
#define __BALL_H__ 1

#include <vector>
#include <cmath>
#include <ctgmath>
#include "../MathLib.h"
#include <ESAT/math.h>
#include <ESAT/time.h>
#include "ESAT_extra/chipmunk/chipmunk.h"
#include "../config.h"
#include "Piece.h"

class Ball: public Piece {
  public:
    Ball(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    Ball(const Ball& orig);
    virtual ~Ball();
    
    virtual void setDynamicPhysics() override;
      
  private:
};

#endif /* __BALL_H__ */