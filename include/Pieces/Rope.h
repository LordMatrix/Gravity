/* Copyright 2016 Marcos Vazquez. All rights reserved.
 *
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>
 *
 * File:   Rope.h
 *
 */
//#ifndef WIN32
//#define WIN32 1
//#endif

#ifndef __ROPE_H__
#define __ROPE_H__ 1

#include <vector>
#include <cmath>
#include <ctgmath>
#include "../MathLib.h"
#include <ESAT/math.h>
#include <ESAT/time.h>
#include "ESAT_extra/chipmunk/chipmunk.h"
#include "../config.h"
#include "Piece.h"

class Rope: public Piece {
  public:
    Rope(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    Rope(const Rope& orig);
    virtual ~Rope();
    
    virtual void setDynamicPhysics() override;
    
  private:
};

#endif /* __ROPE_H__ */