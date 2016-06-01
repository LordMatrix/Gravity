/* Copyright 2016 Marcos Vazquez. All rights reserved.
 *
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>
 *
 * File:   Piece.h
 * Represents a physics body controllable by the player.
 * This class is effectively abstract. It MUST be inherited and its methods must be overriden.
 *
 */
//#ifndef WIN32
//#define WIN32 1
//#endif

#ifndef __CONVEYORBELT_H__
#define __CONVEYORBELT_H__ 1

#include <vector>
#include <cmath>
#include <ctgmath>
#include "../MathLib.h"
#include <ESAT/math.h>
#include <ESAT/time.h>
#include "ESAT_extra/chipmunk/chipmunk.h"
#include "../config.h"
#include "Piece.h"

class ConveyorBelt: public Piece {
  public:
    ConveyorBelt(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    ConveyorBelt(const ConveyorBelt& orig);
    virtual ~ConveyorBelt();
    
  private:
};

#endif /* __CONVEYORBELT_H__ */