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
  frame_ = 0;
  background_ = ESAT::SpriteFromFile("assets/background/intro_background.png");
  cursor_sprite_ = ESAT::SpriteFromFile("assets/UI/Crosshair_02.png");  
  button_background_ = ESAT::SpriteFromFile("assets/UI/button_bg.png");
}

Intro::Intro(const Intro& orig) {
}

Intro::~Intro() {
}

void Intro::Update() {
  if (click_) {
//    Manager::getInstance()->screen_ = new MainMenu();
  }
  
  frame_+=2;
}

void Intro::Draw() {
  DrawBegin();
  
  ESAT::DrawSetTextSize(90);
  ESAT::DrawSetFillColor(255, 255, 255, 200);
  ESAT::DrawText(330.0f, 250.0f, "The Battle for Pass");
  ESAT::DrawSetFillColor(255, 255, 255, frame_);
  ESAT::DrawSetTextSize(30);
  ESAT::DrawText(550.0f, 350.0f, "Click to continue");
  
  DrawEnd();
}
