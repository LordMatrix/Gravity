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
  background_ = MOMOS::SpriteFromFile("src/Gravity/assets/img/intro_bg.jpg");
  createButtons();
}

LevelSelect::LevelSelect(const LevelSelect& orig) {
}

LevelSelect::~LevelSelect() {
}

void LevelSelect::Update(double delta) {
  if (MOMOS::IsSpecialKeyDown(MOMOS::kSpecialKey_Escape)) {
    Intro* intro = new Intro();
    Manager::getInstance()->screen_ = intro;
  } else {
    if (MOMOS::MouseButtonDown(0)) {
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
  
  MOMOS::DrawSetTextSize(80);
  MOMOS::DrawText(500.0f, 150.0f, "Select Level");
  
  DrawButtons();
  
  MOMOS::DrawSprite(cursor_sprite_, (float)MOMOS::MousePositionX(), (float)MOMOS::MousePositionY());
  
  MOMOS::DrawEnd();
  MOMOS::WindowFrame();
}


void LevelSelect::createButtons() {
  float menu_x = kWinWidth - kMenuWidth;
  float width = 180.0f;
  float height = 50.0f;
  
  MOMOS::SpriteHandle bg = MOMOS::SpriteFromFile("src/Gravity/assets/img/btn_bg.png");
  
  //Create editor at position 0
  buttons_.push_back(new Button(500.0f, 650.0f, height, width*2, 0, bg, "LEVEL EDITOR", true));
  
  //Load level names
  std::vector<std::string> names = Level::LoadLevelNames();
  
  //Create level buttons
  int i = 0;
  float x = 25.0f;
  float y = 200.0f;
  for (i=0; i<names.size(); i++) {
    buttons_.push_back(new Button(x, y, height, width, 0, bg, std::to_string(i+1)+" - "+names[i], true));
    x += 200.0f;
    if (i%5 == 0 && i!=0) {
      x = 25.0f;
      y += 100.0f; 
    }
  }
  
  Manager::getInstance()->num_levels_ = i;
}


void LevelSelect::DrawButtons() {
  for (int i=0; i<buttons_.size(); i++) {
    buttons_[i]->draw();
  }
}