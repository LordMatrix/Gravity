/* Copyright 2015 Marcos Vazquez. All rights reserved.    
 * 
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>  
 * Created on may 10, 2016, 05:16 PM
 *
 * File:   Level.h                                              
 * A class that represents an in-game level
 *
 */

#ifndef LEVEL_H
#define LEVEL_H 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <MOMOS/sprite.h>
#include <MOMOS/window.h>

#include <chipmunk/chipmunk.h>
#include <sqlite3.h>

#include "Pieces/Piece.h"
#include "Pieces/SmallRamp.h"
#include "Pieces/LargeRamp.h"
#include "Pieces/Wall.h"
#include "Pieces/ConveyorBelt.h"
#include "Pieces/Spring.h"
#include "Pieces/Bouncer.h"
#include "Pieces/Ball.h"
#include "Pieces/BowlingBall.h"
#include "Pieces/SeeSaw.h"
#include "Pieces/Rope.h"
#include "Pieces/Goal.h"

class Level {
  
  public:

    Level();
    Level(int id, Piece* ball, Piece* goal, cpSpace* space);
    Level(const Level& orig);
    ~Level();
    
    void load(int id, cpSpace* space);
    static std::vector<std::string> LoadLevelNames();
    
    int id_;
    std::string name_;
    bool won_;
    std::vector<Piece*> pieces_;
    
     MathLib::Point2 eject_point_;
     std::vector<Piece*> inventory_pieces_;
     std::vector<Piece*> fixed_pieces_;
     
     Piece* ball_;
     Piece* goal_;
    
   
  private:
    
};

#endif /* LEVEL_H */

