/* Copyright 2016 Marcos Vazquez. All rights reserved.
 *
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>
 *
 * File:   main.cc               
 * An Incredible Machine / Isaac Newton's Gravity ripoff with focus on physics simulation.
 *
 */

//#ifndef WIN32
//#define WIN32 1
//#endif

#include "ESAT/window.h"
#include "ESAT/draw.h"
#include "ESAT/input.h"
 
#include <iostream>
#include "time.h"

#include "../include/Pieces/Piece.h"
#include "ESAT_extra/chipmunk/chipmunk.h" 
#include "../include/config.h"
#include "../include/Manager.h"


/**
 * @brief The alpha and the omega 
 */
int ESAT::main(int argc, char **argv) {

  srand(time(NULL));

  ESAT::WindowInit(kWinWidth, kWinHeight);
  
  static double last_time = ESAT::Time();
  
  while (ESAT::WindowIsOpened() && !Manager::getInstance()->quit_game_) {
    
    if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape))
      Manager::getInstance()->quit_game_ = true;
    
    /****************SIMULATION****************/
    double tick = ESAT::Time();
    double delta = (tick - last_time) * 0.1f;
    last_time = ESAT::Time();
  
    //GameLoop
    Manager::getInstance()->screen_->Input();
    Manager::getInstance()->screen_->Update(delta);
    Manager::getInstance()->screen_->Draw();
  }
  
  ESAT::WindowDestroy();
  return 0;
}