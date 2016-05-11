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
#include <ESAT/sprite.h>
#include <ESAT/window.h>
#include "Level.h"

class Level {
  
  public:

    //Maps inside the game
    enum LevelId {
      kLevel_Tutorial
    };

    Level();
    Level(const Level& orig);
    ~Level();

    void LoadFromFile(std::string filename, Level* levels[10]);
   
    LevelId id_;
   
  private:
    
};

#endif /* LEVEL_H */

