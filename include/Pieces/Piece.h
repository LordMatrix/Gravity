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

#ifndef __PIECE_H__
#define __PIECE_H__ 1

#include <vector>
#include <cmath>
#include <ctgmath>
#include "../MathLib.h"
#include <ESAT/math.h>
#include <ESAT/time.h>
#include "ESAT_extra/chipmunk/chipmunk.h"
#include "../config.h"

class Piece {
  public:
    Piece();
    Piece(MathLib::Point2 initial_pos, bool is_static, int collision_type, cpSpace* space);
    Piece(const Piece& orig);
    virtual ~Piece();

    virtual void update();
    virtual void move();
    virtual void draw();
    void setPhysics();
    virtual void setDynamicPhysics();
    virtual void setStaticPhysics();
    
    bool checkClick();
    bool checkHover();
    void drop();
    
    ESAT::SpriteHandle img_;
    bool static_;
    bool dragged_;
    bool active_;
    int colspan_;
    bool movable_;
    
    std::vector<MathLib::Point2> points_;
    //Position at level start
    MathLib::Vec2 initial_pos_;
    //Position set by the player
    MathLib::Vec2 set_pos_;
    //Position set by the simulation
    MathLib::Vec2 current_pos_;
    float rotation_;
    
    float height_;
    float width_;
    MathLib::Point2 img_pivot_;
    
    double last_update_;
    
    cpSpace* space_;    
    cpBody* physics_body_;
    cpShape* physics_shape_;
    std::vector<cpShape*> physics_segments_;
    cpCollisionType collision_type_;
    
  protected:
    std::vector<MathLib::Point2> floatToPoints(float* arr, int length);
    float* pointsToFloat(std::vector<MathLib::Point2> points);
};

#endif /* __PIECE_H__ */