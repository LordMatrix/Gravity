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

#ifndef __BOUNCER_H__
#define __BOUNCER_H__ 1

#include <vector>
#include <cmath>
#include <ctgmath>
#include "../MathLib.h"
#include <MOMOS/math.h>
#include <MOMOS/time.h>
#include <chipmunk/chipmunk.h>
#include "../config.h"
#include "Piece.h"

class Bouncer: public Piece {
  public:
    Bouncer(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    Bouncer(const Bouncer& orig);
    virtual ~Bouncer();
    
    virtual void setStaticPhysics() override;
    
  private:
};

#endif /* __BOUNCER_H__ */