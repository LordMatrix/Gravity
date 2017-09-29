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
  background_ = MOMOS::SpriteFromFile("src/Gravity/assets/img/intro_bg.jpg");
}

Intro::Intro(const Intro& orig) {
}

Intro::~Intro() {
}

void Intro::Update(double delta) {
  if (MOMOS::IsSpecialKeyDown(MOMOS::kSpecialKey_Escape))
      Manager::getInstance()->quit_game_ = true;
  
  if (click_) {
    Manager::getInstance()->screen_ = new LevelSelect();
  }
}

void Intro::Draw() {
  MOMOS::DrawBegin();
  MOMOS::DrawClear(255,255,255);

  MOMOS::Mat3 transform;
  float ratiox = (float)kWinWidth / (float)MOMOS::SpriteWidth(background_);
  float ratioy = (float)kWinHeight / (float)MOMOS::SpriteHeight(background_);
  
  MOMOS::Mat3InitAsScale(ratiox, ratioy, &transform);
  MOMOS::DrawSpriteWithMatrix(background_, transform);
  
  /************ TEXT ************/
  InitText();
  MOMOS::DrawSetFillColor(0,0,0,255);
  MOMOS::DrawSetStrokeColor(0,0,0,255);
  
  MOMOS::DrawSetTextSize(120);
  MOMOS::DrawText(330.0f, 250.0f, "Galileo's Gravity");
  MOMOS::DrawSetTextSize(60);
  MOMOS::DrawText(550.0f, 500.0f, "Click to continue");
  
  MOMOS::DrawSprite(cursor_sprite_, (float)MOMOS::MousePositionX(), (float)MOMOS::MousePositionY());
  
  MOMOS::DrawEnd();
  MOMOS::WindowFrame();
}
