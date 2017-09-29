/* Copyright 2016 Marcos Vazquez. All rights reserved.
 *
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>
 *
 * File:   BowlingBall.h
 *
 */
//#ifndef WIN32
//#define WIN32 1
//#endif

#ifndef __BOWLINGBALL_H__
#define __BOWLINGBALL_H__ 1

#include <vector>
#include <cmath>
#include <ctgmath>
#include "../MathLib.h"
#include <MOMOS/math.h>
#include <MOMOS/time.h>
#include <chipmunk/chipmunk.h>
#include "../config.h"
#include "Piece.h"

class BowlingBall: public Piece {
  public:
    BowlingBall(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    BowlingBall(const BowlingBall& orig);
    virtual ~BowlingBall();
    
    virtual void setDynamicPhysics() override;
      
  private:
};

#endif /* __BOWLINGBALL_H__ */