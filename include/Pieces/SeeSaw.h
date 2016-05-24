/* Copyright 2016 Marcos Vazquez. All rights reserved.
 *
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>
 *
 * File:   SeeSaw.h
 *
 */
//#ifndef WIN32
//#define WIN32 1
//#endif

#ifndef __SEESAW_H__
#define __SEESAW_H__ 1

#include <vector>
#include <cmath>
#include <ctgmath>
#include "../MathLib.h"
#include <ESAT/math.h>
#include <ESAT/time.h>
#include "ESAT_extra/chipmunk/chipmunk.h"
#include "../config.h"
#include "Piece.h"

class SeeSaw: public Piece {
  public:
    SeeSaw(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    SeeSaw(const SeeSaw& orig);
    virtual ~SeeSaw();
    
    virtual void setDynamicPhysics() override;
    
  private:
};

#endif /* __SEESAW_H__ */