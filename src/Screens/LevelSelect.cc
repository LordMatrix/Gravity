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
  background_ = ESAT::SpriteFromFile("assets/img/intro_bg.jpg");
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
      //Open level editor
      if (btn == 0) {
        LevelEditor* editor = new LevelEditor();
        Manager::getInstance()->screen_ = editor;
      } else if (btn > -1) {
        Game* game = new Game();
        Manager::getInstance()->screen_ = game;
        game->current_index_ = btn - 2;
        game->levelUp();
      }
    }
  }
}

void LevelSelect::Draw() {
  ESAT::DrawBegin();
  ESAT::DrawClear(255,255,255);
  
  ESAT::Mat3 transform;
  float ratiox = (float)kWinWidth / (float)ESAT::SpriteWidth(background_);
  float ratioy = (float)kWinHeight / (float)ESAT::SpriteHeight(background_);
  
  ESAT::Mat3InitAsScale(ratiox, ratioy, &transform);
  ESAT::DrawSpriteWithMatrix(background_, transform);
  
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
  float width = 180.0f;
  float height = 50.0f;
  
  ESAT::SpriteHandle bg = ESAT::SpriteFromFile("assets/img/btn_bg.png");
  
  //Create editor at position 0
  buttons_.push_back(new Button(500.0f, 650.0f, height, width*2, 0, bg, "LEVEL EDITOR", true));
  
  buttons_.push_back(new Button(25.0f, 200.0f, height, width, 0, bg, "1 - Ramps", true));
  buttons_.push_back(new Button(225.0f, 200.0f, height, width, 0, bg, "2 - Walls", true));
  buttons_.push_back(new Button(425.0f, 200.0f, height, width, 0, bg, "3 - Bumpers", true));
  buttons_.push_back(new Button(625.0f, 200.0f, height, width, 0, bg, "4 - Conveyors", true));
  buttons_.push_back(new Button(25.0f, 400.0f, height, width, 0, bg, "5 - Springs", true));
  buttons_.push_back(new Button(225.0f, 400.0f, height, width, 0, bg, "6 - Levers", true));
}


void LevelSelect::DrawButtons() {
  for (int i=0; i<buttons_.size(); i++) {
    buttons_[i]->draw();
  }
}