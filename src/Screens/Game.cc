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
  for (int i=pieces_.size()-1; i>=0; i--) {
    delete pieces_[i];
  }
  pieces_.clear();
  Init();
}


/// @brief Creates buttons and loads stats background
void Game::Init() {
  
  physics_ = new Physics();
  
  physics_->space_ = cpSpaceNew();
  
  cpSpaceSetGravity(physics_->space_, cpv(0, 0.0098f));
  
  Piece* piece = new Piece();
  piece->space_ = physics_->space_;
  piece->initial_pos_ = {900.0f, 500.0f};
  piece->set_pos_ = piece->initial_pos_;
  piece->current_pos_ = piece->initial_pos_;
  piece->static_ = true;
  pieces_.push_back(piece);
  
  Piece* piece2 = new Piece();
  piece2->space_ = physics_->space_;
  piece2->static_ = false;
  pieces_.push_back(piece2);
  
  //BALL
  Piece* ball = new Piece();
  ball->space_ = physics_->space_;
  ball->static_ = false;
  ball->collision_type_ = BALL_TYPE;
  
  ball->points_.clear();
  MathLib::Vec2 position_offset = {0.0f, 0.0f};
  MathLib::assignRegularPolygon(20, 30, position_offset, 0.0f, ball->points_);
  ball->initial_pos_ = {100.0f, 0.0f};
  ball->set_pos_ = ball->initial_pos_;
  ball->current_pos_ = ball->initial_pos_;
  
  ball_ = ball;
  pieces_.push_back(ball);
  
  
  //GOAL
  Piece* goal = new Piece();
  goal->space_ = physics_->space_;
  goal->initial_pos_ = {100.0f, 600.0f};
  goal->set_pos_ = goal->initial_pos_;
  goal->current_pos_ = goal->initial_pos_;
  goal->static_ = true;
  goal->collision_type_ = GOAL_TYPE;
  
  goal_ = goal;
  pieces_.push_back(goal);
  
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
  for (int i=0; i<pieces_.size(); i++) {
    pieces_[i]->draw();
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

    for (int i=0; i<pieces_.size(); i++) {
      pieces_[i]->update();
    }
  } else if (!physics_->simulation_started_) {
    
    for (int i=0; i<pieces_.size(); i++) {
      
      //Detect drag/drop
      if (ESAT::MouseButtonDown(0)) {
        if (pieces_[i]->checkClick()) {
          pieces_[i]->dragged_ = !pieces_[i]->dragged_;
        }
      }
      
      //Move selected piece along with the mouse
      if (pieces_[i]->dragged_) {
        pieces_[i]->drop();
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


void Game::startSimulation() {
  physics_->startSimulation();
  
  for (int i=0; i<pieces_.size(); i++) {
    pieces_[i]->space_ = physics_->space_;
    pieces_[i]->physics_segments_.clear();
  }
  
  //Update pieces physics
//  if (!physics_->simulation_started_) {
    ball_->current_pos_ = {100.0f, 0.0f};
    
    for (int i=0; i<pieces_.size(); i++) {
      //Check if the piece is inside the menu
      float menu_x = kWinWidth - menu_width_;
      //Update active status
      pieces_[i]->active_ = (pieces_[i]->current_pos_.x < menu_x);
        
      if (pieces_[i]->active_)
        pieces_[i]->setPhysics();
    }
//  }
}


void Game::stopSimulation() {
  for (int i=0; i<pieces_.size(); i++) {
    pieces_[i]->current_pos_ = pieces_[i]->set_pos_;
    pieces_[i]->setPhysics();
  }
  physics_->stopSimulation();
}