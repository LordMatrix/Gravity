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
#include <ESAT/sprite.h>
#include <ESAT/window.h>

#include "ESAT_extra/chipmunk/chipmunk.h" 

#include "Pieces/Piece.h"
#include "Pieces/SmallRamp.h"
#include "Pieces/LargeRamp.h"

class Level {
  
  public:

    //Maps inside the game
    enum LevelId {
      kLevel_Tutorial
    };

    Level();
    Level(int id, Piece* ball, Piece* goal, cpSpace* space);
    Level(const Level& orig);
    ~Level();

    void LoadFromFile(std::string filename, Level* levels[10]);
   
    LevelId id_;
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

