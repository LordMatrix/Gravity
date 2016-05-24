/* 
 * File:   LevelSelect.cc
 * Author: Marcos Vazquez
 * 
 * Created on November 15, 2015, 11:55 PM
 */

#include "../../include/Screens/LevelSelect.h"

/** @brief
 *
 *
 *
 *  @return
 *  @param
 *  @param
 */
LevelSelect::LevelSelect() {
  createButtons();
}

LevelSelect::LevelSelect(const LevelSelect& orig) {
}

LevelSelect::~LevelSelect() {
}

void LevelSelect::Update(double delta) {
  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    Intro* intro = new Intro();
    Manager::getInstance()->screen_ = intro;
  } else {
    if (ESAT::MouseButtonDown(0)) {
      int btn = CheckButtonsClick();
      printf("%d\n",btn);
      if (btn > -1) {
        Game* game = new Game();
        Manager::getInstance()->screen_ = game;
        game->current_level_ = game->levels_[btn];
      }
    }
  }
}

void LevelSelect::Draw() {
  ESAT::DrawBegin();
  ESAT::DrawClear(255,255,255);

//  ESAT::Mat3 transform;
//  float ratiox = (float)kWinWidth / (float)ESAT::SpriteWidth(background_);
//  float ratioy = (float)kWinHeight / (float)ESAT::SpriteHeight(background_);
//  
//  ESAT::Mat3InitAsScale(ratiox, ratioy, &transform);
//  ESAT::DrawSpriteWithMatrix(background_, transform);
  
  /************ TEXT ************/
  InitText();
  ESAT::DrawSetFillColor(0,0,0,255);
  ESAT::DrawSetStrokeColor(0,0,0,255);
  
  ESAT::DrawSetTextSize(80);
  ESAT::DrawText(500.0f, 150.0f, "Select Level");
  
  DrawButtons();
  
  ESAT::DrawSprite(cursor_sprite_, (float)ESAT::MousePositionX(), (float)ESAT::MousePositionY());
  
  ESAT::DrawEnd();
  ESAT::WindowFrame();
}


void LevelSelect::createButtons() {
  float x = kWinWidth - kMenuWidth;

  buttons_.push_back(new Button(25.0f, 200.0f, 50.0f, 50.0f, 0, nullptr, "1 - Ramps", false));
  buttons_.push_back(new Button(225.0f, 200.0f, 50.0f, 50.0f, 0, nullptr, "2 - Walls", false));
  buttons_.push_back(new Button(425.0f, 200.0f, 50.0f, 50.0f, 0, nullptr, "3 - Bumpers", false));
  buttons_.push_back(new Button(625.0f, 200.0f, 50.0f, 50.0f, 0, nullptr, "4 - Conveyors", false));
  
  buttons_.push_back(new Button(25.0f, 400.0f, 50.0f, 50.0f, 0, nullptr, "5 - Springs", false));
  buttons_.push_back(new Button(225.0f, 400.0f, 50.0f, 50.0f, 0, nullptr, "6 - Levers", false));
}