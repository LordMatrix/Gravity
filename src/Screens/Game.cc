/* 
 * File:   Game.cc
 * Author: Marcos Vazquez
 * 
 * Created on November 15, 2015, 12:13 AM
 */

#include "../../include/Screens/Game.h"

Game::Game() {
  Screen();
  Init();
}

Game::Game(const Game& orig) {
}

Game::~Game() {
}


void Game::restartLevel() {
  //Delete previous pieces
  for (int i=current_level_->pieces_.size()-1; i>=0; i--) {
    delete current_level_->pieces_[i];
  }
  current_level_->pieces_.clear();
  Init();
}


/// @brief Creates buttons and loads stats background
void Game::Init() {
  
  physics_ = new Physics();
  
  physics_->space_ = cpSpaceNew();
  
  cpSpaceSetGravity(physics_->space_, cpv(0, 0.0098f));
  
  loadLevels();
  current_level_ = levels_[0];

  ball_ = current_level_->ball_;
  goal_ = current_level_->goal_;
          
  CreateButtons();
}


void Game::Input() {

}


void Game::Draw() {
  ESAT::DrawBegin();
  ESAT::DrawClear(255,255,255);


  /************ MENU ************/
  ESAT::DrawSetFillColor(0,0,200,200);
  ESAT::DrawSetStrokeColor(255,255,255,255);
  
  //Draw menu background
  float x = kWinWidth - menu_width_;
  float path[] = {x,0.0f, x,kWinHeight, kWinWidth,kWinHeight, kWinWidth,0.0f, x,0.0f};
  ESAT::DrawSolidPath(path, 5);
  
  //Draw Buttons
  for (int i=0; i<buttons_.size(); i++) {
    buttons_[i]->draw(); 
  }
  /******************************/

  //Draw Pieces
  for (int i=0; i<current_level_->pieces_.size(); i++) {
    current_level_->pieces_[i]->draw();
  }
  
  ESAT::DrawSprite(cursor_sprite_, (float)ESAT::MousePositionX(), (float)ESAT::MousePositionY());
  
  
  physics_->drawPhysics();
  
  ESAT::DrawEnd();
  ESAT::WindowFrame();
}


void Game::Update(double delta) {
  //Listen to button click
  if (ESAT::MouseButtonPressed(0)) {
    for (int i=0; i<buttons_.size(); i++) {
      if (buttons_[i]->checkClick()) {
        switch(i) {
          case 0:
            //Play
            if (!physics_->simulation_started_) {
              startSimulation();
            } else {
              physics_->resumeSimulation();
            }
            break;
          case 1:
            physics_->pauseSimulation();
            break;
          case 2:
            stopSimulation();
            break;
        }
        
      }
    }
  }
  
  //Listen to spacebar press
  if (ESAT::GetNextPressedKey()) {
    if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Space)) {
      
      //Update pieces physics
      if (!physics_->simulation_started_) {
        startSimulation();
      } else {
        if (physics_->simulation_running_) physics_->pauseSimulation();
        else physics_->resumeSimulation();
      }
    }
  }
  
  if (physics_->simulation_running_) {
    cpSpaceStep(physics_->space_, delta);

    for (int i=0; i<current_level_->pieces_.size(); i++) {
      current_level_->pieces_[i]->update();
    }
  } else if (!physics_->simulation_started_) {
    
    for (int i=0; i<current_level_->pieces_.size(); i++) {
      
      //Detect drag/drop
      if (ESAT::MouseButtonDown(0)) {
        if (current_level_->pieces_[i]->checkClick()) {
          current_level_->pieces_[i]->dragged_ = !current_level_->pieces_[i]->dragged_;
        }
      }
      
      //Move selected piece along with the mouse
      if (current_level_->pieces_[i]->dragged_) {
        current_level_->pieces_[i]->drop();
      }
    }
  }
}


void Game::CreateButtons() {
  printf("CREATING BUTTONS\n");
  float x = kWinWidth - menu_width_;

  //Play button
  buttons_.push_back(new Button(x + 25.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/play.png"), "", false));
  //Pause Button
  buttons_.push_back(new Button(x + 125.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/pause.png"), "", false));
  //Stop button
  buttons_.push_back(new Button(x + 225.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/stop.png"), "", false));
}


void Game::loadLevels() {
  Level* lvl = new Level(0, ball_, goal_, physics_->space_);
  levels_.push_back(lvl);
}


void Game::startSimulation() {
  physics_->startSimulation();
  
  for (int i=0; i<current_level_->pieces_.size(); i++) {
    current_level_->pieces_[i]->space_ = physics_->space_;
    current_level_->pieces_[i]->physics_segments_.clear();
  }
  
  //Update pieces physics
//  if (!physics_->simulation_started_) {
    ball_->current_pos_ = {100.0f, 0.0f};
    
    for (int i=0; i<current_level_->pieces_.size(); i++) {
      //Check if the piece is inside the menu
      float menu_x = kWinWidth - menu_width_;
      //Update active status
      current_level_->pieces_[i]->active_ = (current_level_->pieces_[i]->current_pos_.x < menu_x);
        
      if (current_level_->pieces_[i]->active_)
        current_level_->pieces_[i]->setPhysics();
    }
//  }
}


void Game::stopSimulation() {
  for (int i=0; i<current_level_->pieces_.size(); i++) {
    current_level_->pieces_[i]->current_pos_ = current_level_->pieces_[i]->set_pos_;
    current_level_->pieces_[i]->setPhysics();
  }
  physics_->stopSimulation();
}