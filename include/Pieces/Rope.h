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
#include <MOMOS/math.h>
#include <MOMOS/time.h>
#include <chipmunk/chipmunk.h>
#include "../config.h"
#include "Piece.h"

class Rope: public Piece {
  public:
    Rope(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    Rope(const Rope& orig);
    virtual ~Rope();
    
    virtual void setDynamicPhysics() override;
    virtual void update() override;
    virtual void draw() override;
    
    std::vector<cpBody*> physics_bodies_;
    std::vector<cpShape*> physics_shapes_;
    std::vector<MathLib::Point2*> points_;
    
    std::vector<MathLib::Vec2*> current_poss_;
    
    int num_segments_;
  private:
};

#endif /* __ROPE_H__ */