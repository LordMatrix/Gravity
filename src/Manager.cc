/* Copyright 2015 Marcos Vazquez. All rights reserved.    
 * 
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>  
 * Created on November 9, 2015, 12:34 PM
 *
 * File:   Manager.cc                                               
 * A singleton class that holds all global variables used throughout the game 
 * or needed by various different classes
 *
 */

#include "../include/Manager.h"


Manager* Manager::instance_ = nullptr;


/// @brief Creates a new Manager, with screen_ defaulting to Intro
Manager::Manager() {
  screen_id_ = kScreen_Intro;
  screen_ = new Intro();
  quit_game_ = false;
}

Manager::Manager(const Manager& orig) {
}

/// @brief Deletes current screen, player and all loaded levels
Manager::~Manager() {
  delete screen_;
}

/// @brief Retrieves the singleton instance
Manager* Manager::getInstance() {
  if(!instance_) {
      instance_ = new Manager();
  }

  return instance_;
}

/// @brief Deletes the current instance and creates a new one from scratch
void Manager::Reset() {
  delete instance_;
  instance_ = nullptr;
  instance_ = new Manager();
}
