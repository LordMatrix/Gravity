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

#include <MOMOS/window.h>
#include <MOMOS/draw.h>
#include <MOMOS/input.h>
#include <MOMOS/time.h>
#include <chipmunk/chipmunk.h>

#include <iostream>
#include "time.h"

#include "../include/Pieces/Piece.h"
#include "../include/config.h"
#include "../include/Manager.h"


/**
 * @brief The alpha and the omega 
 */
int main(int argc, char **argv) {

  srand(time(NULL));

  MOMOS::WindowInit(kWinWidth, kWinHeight);
  
  static double last_time = MOMOS::Time();
  
  while (MOMOS::WindowIsOpened() && !Manager::getInstance()->quit_game_) {
    
    /****************SIMULATION****************/
    double tick = MOMOS::Time();
    double delta = (tick - last_time) * 0.1f;
    last_time = MOMOS::Time();
  
    //GameLoop
    Manager::getInstance()->screen_->Input();
    Manager::getInstance()->screen_->Update(delta);
    Manager::getInstance()->screen_->Draw();
  }
  
  MOMOS::WindowDestroy();
  return 0;
}