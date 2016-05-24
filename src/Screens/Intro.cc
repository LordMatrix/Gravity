/* 
 * File:   Intro.cc
 * Author: Marcos Vazquez
 * 
 * Created on November 15, 2015, 11:55 PM
 */

#include "../../include/Screens/Intro.h"

/** @brief
 *
 *
 *
 *  @return
 *  @param
 *  @param
 */
Intro::Intro() {
  background_ = ESAT::SpriteFromFile("assets/img/intro_bg.jpg");
}

Intro::Intro(const Intro& orig) {
}

Intro::~Intro() {
}

void Intro::Update(double delta) {
  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape))
      Manager::getInstance()->quit_game_ = true;
  
  if (click_) {
    Manager::getInstance()->screen_ = new LevelSelect();
  }
}

void Intro::Draw() {
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
  
  ESAT::DrawSetTextSize(120);
  ESAT::DrawText(330.0f, 250.0f, "Galileo's Gravity");
  ESAT::DrawSetTextSize(60);
  ESAT::DrawText(550.0f, 500.0f, "Click to continue");
  
  ESAT::DrawSprite(cursor_sprite_, (float)ESAT::MousePositionX(), (float)ESAT::MousePositionY());
  
  ESAT::DrawEnd();
  ESAT::WindowFrame();
}
