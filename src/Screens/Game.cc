/* 
 * File:   Game.cc
 * Author: Marcos Vazquez
 * 
 * Created on November 15, 2015, 12:13 AM
 */

#include "../../include/Screens/Game.h"

Game::Game() {
  Screen();
  current_index_ = 0;
  Init();
  
  background_ = ESAT::SpriteFromFile("assets/img/game_bg.png");
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
  current_level_ = levels_[current_index_];

  ball_ = current_level_->ball_;
  goal_ = current_level_->goal_;
          
  CreateButtons();
}


void Game::Draw() {
  ESAT::DrawBegin();
  ESAT::DrawClear(255,255,255);

  ESAT::Mat3 transform;
  float ratiox = (float)kWinWidth / (float)ESAT::SpriteWidth(background_);
  float ratioy = (float)kWinHeight / (float)ESAT::SpriteHeight(background_);
  
  ESAT::Mat3InitAsScale(ratiox, ratioy, &transform);
  ESAT::DrawSpriteWithMatrix(background_, transform);
  
  /************ MENU ************/
  ESAT::DrawSetFillColor(0,0,200,200);
  ESAT::DrawSetStrokeColor(255,255,255,255);
  
  //Draw menu background
  float x = kWinWidth - kMenuWidth;
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
  
  if (kDebug) {
    physics_->drawPhysics();
  }

  //Print winning texts
  if(physics_->ball_caged_) {
    //Display winning message
    ESAT::DrawSetTextSize(80.0f);
    ESAT::DrawText(kWinWidth/3, 100.0f, "You Win");
    //Display "next level" button
    if (!current_level_->won_) {
      buttons_.push_back(new Button((float)kWinWidth/3, (float)115.0f, 50.0f, 200.0f, 0, nullptr, "Click here for next Level", false));
      current_level_->won_ = true;
    }
  }
  
  
  //Print mouse coordinates
  InitText();
  ESAT::DrawSetTextSize(15.0f);
  ESAT::DrawText(10.0f, 20.0f, (std::to_string((int)ESAT::MousePositionX())+", "+std::to_string((int)ESAT::MousePositionY())).c_str());
  
  ESAT::DrawEnd();
  ESAT::WindowFrame();
}


void Game::Update(double delta) {
  
  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    LevelSelect* ls = new LevelSelect();
    Manager::getInstance()->screen_ = ls;
    return;
  }
  //FOR DEBUGGING. DELETE ON RELEASE.
  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Enter)) {
    levelUp();
  }
  
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
          case 3:
            //Next level
            levelUp();
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
    
    //Check clicking on pieces
    bool found = false;
    for (int i=0; i<current_level_->pieces_.size() && !found; i++) {
      
      //Detect drag/drop
      if (current_level_->pieces_[i]->movable_) {
        if (ESAT::MouseButtonDown(0)) {
          
          if (current_level_->pieces_[i]->checkClick()) {
            current_level_->pieces_[i]->dragged_ = !current_level_->pieces_[i]->dragged_;
            found = true;
          }
        }

        //Move selected piece along with the mouse
        if (current_level_->pieces_[i]->dragged_) {
          current_level_->pieces_[i]->drop();
        }
      }
    }
  }
}


void Game::CreateButtons() {
  float x = kWinWidth - kMenuWidth;

  //Play button
  buttons_.push_back(new Button(x + 25.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/play.png"), "", false));
  //Pause Button
  buttons_.push_back(new Button(x + 125.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/pause.png"), "", false));
  //Stop button
  buttons_.push_back(new Button(x + 225.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/stop.png"), "", false));
}


void Game::deleteButtons() {
  for (int i=0; i<buttons_.size(); i++) {
    delete buttons_[i];
  }
  buttons_.clear();
}


void Game::loadLevels() {
  Level* lvl;
  
  for (int i=0; i<Manager::getInstance()->num_levels_; i++) {
    lvl = new Level(i+1, ball_, goal_, physics_->space_);
    levels_.push_back(lvl);
  }
}


void Game::levelUp() {
  //Go to next level, if there is a next level
  if (current_index_ < Manager::getInstance()->num_levels_-1) {
    current_index_++;
    current_level_ = levels_[current_index_];

    ball_ = current_level_->ball_;
    goal_ = current_level_->goal_;
    
    
    stopSimulation();
    physics_->ball_caged_ = false;
    
    deleteButtons();
    CreateButtons();
  }
}


void Game::startSimulation() {
  physics_->startSimulation();
  
  for (int i=0; i<current_level_->pieces_.size(); i++) {
    current_level_->pieces_[i]->space_ = physics_->space_;
    current_level_->pieces_[i]->physics_segments_.clear();
  }
  
  //Update pieces physics
  ball_->current_pos_ = ball_->initial_pos_;

  for (int i=0; i<current_level_->pieces_.size(); i++) {
    //Check if the piece is inside the menu
    float menu_x = kWinWidth - kMenuWidth;
    //Update active status
    current_level_->pieces_[i]->active_ = (current_level_->pieces_[i]->current_pos_.x < menu_x);

    if (current_level_->pieces_[i]->active_)
      current_level_->pieces_[i]->setPhysics();
  }

  Manager::getInstance()->ball_ = ball_;
}


void Game::stopSimulation() {
  for (int i=0; i<current_level_->pieces_.size(); i++) {
    current_level_->pieces_[i]->current_pos_ = current_level_->pieces_[i]->set_pos_;
    current_level_->pieces_[i]->setPhysics();
  }
  
  ball_->rotation_ = 0.0f;
  
  physics_->stopSimulation();
}