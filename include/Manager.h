/* Copyright 2015 Marcos Vazquez. All rights reserved.    
 * 
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>  
 * Created on November 9, 2015, 12:34 PM
 *
 * File:   Manager.h                                              
 * A class that holds all global variables used throughout the game 
 * or needed by various different classes
 *
 */

#ifndef MANAGER_H
#define MANAGER_H 1

#include "../include/config.h"
#include "Screens/Screen.h"
#include "Screens/Intro.h"
#include "Screens/LevelSelect.h"
#include "Screens/Game.h"
#include "Level.h"
#include "Pieces/Piece.h"

class Manager {
public:
    //Screens in the game
    enum ScreenId {
      kScreen_Intro,
      kScreen_LevelSelect,
      kScreen_Game,
    };
    
    static Manager* getInstance();
    static void Reset();
    
    ScreenId screen_id_;
    Screen* screen_;
    int quit_game_;
  
    Piece* ball_;

private:
    
    Manager();
    Manager(const Manager& orig);
    ~Manager();
    
    static Manager* instance_;
};

#endif /* MANAGER_H */

