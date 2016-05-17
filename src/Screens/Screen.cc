/* 
 * File:   Screen.cc
 * Author: Marcos Vazquez
 * 
 * Created on November 15, 2015, 11:55 PM
 */

#include "../../include/Screens/Screen.h"

const int kWindowWidth = 1366;
const int kWindowHeight = 768;

/// @brief Creates a screen and loads its sprites
Screen::Screen() {
    cursor_sprite_ = ESAT::SpriteFromFile("assets/img/Crosshair_02.png");
    background_ = ESAT::SpriteFromFile("assets/img/sky.jpg");
    button_background_ = ESAT::SpriteFromFile("assets/img/button_bg.png");
    Init();
}

Screen::Screen(const Screen& orig) {
}

Screen::~Screen() {
//  ESAT::SpriteRelease(background_);
  ESAT::SpriteRelease(cursor_sprite_);
  ESAT::SpriteRelease(button_background_);

  for (int i=0; i<buttons_.size(); i++) {
//    delete(buttons_[i]);
  }
}

void Screen::Init() {
  InitText();
}

/** @brief  Common drawn elements and functions called in every screen
 *
 *  This method must be called at the start of every Draw cycle.
 *  Draws screen background.
 *
 */
void Screen::DrawBegin() {
  ESAT::DrawBegin();
  ESAT::DrawClear(255, 255, 255);
  
  //Draw background image
  float sprite_width = ESAT::SpriteWidth(background_);
  float sprite_height = ESAT::SpriteHeight(background_);
  ESAT::Mat3 escale;
  ESAT::Mat3InitAsScale((float)kWindowWidth/sprite_width, (float)kWindowHeight/sprite_height, &escale);
  ESAT::DrawSpriteWithMatrix(background_, escale);
  
  DrawButtons();
}

/** @brief Common finishing drawing functions called in every screen
 *
 *  This method must be called at the start of every Draw cycle.
 *  Draws cursor sprite and updates screen to the next frame.
 *
 */
void Screen::DrawEnd() {
  DrawCursor();
  ESAT::DrawEnd();
  ESAT::WindowFrame();
}

/// @brief Detects mouse click
void Screen::Input() {
  click_ = ESAT::MouseButtonUp(0);
}

/** @brief Updates the screen
 */
void Screen::Update(double delta) {

}

/// @brief Draws the screen
void Screen::Draw() {
  DrawBegin();
  
  ESAT::DrawText(300.0f, 50.0f, "The Battle for Pass - SuperGeneric Screen");
  
  DrawEnd();
}

/** @brief Draws the cursor
 *  Draws the sprite cursor_sprite_ on the mouse coordinates
 */
void Screen::DrawCursor() {
  ESAT::DrawSprite(cursor_sprite_, (float)ESAT::MousePositionX(), (float)ESAT::MousePositionY());
}

/// @brief Creates buttons for the current screen
void Screen::CreateButtons() {
 printf("generic buttons\n");
}


/// @brief  Draws all t_Buttons contained within buttons_
void Screen::DrawButtons() {
  float x = 0.0f;
  float y = 0.0f;
  float height = 0.0f;
  float width = 0.0f;
  float margin = 30.0f;

  for (int i = 0; i < buttons_.size(); i++) {
    x = buttons_[i]->pos_.x;
    y = buttons_[i]->pos_.y;
    height = buttons_[i]->height_;
    width = buttons_[i]->width_;

    if (buttons_[i]->border_) {
      float path_points[] = { x, y,
        x + width, y,
        x + width, y + height,
        x, y + height,
        x, y
      };

      /*rgb colors inside the polygon*/
      ESAT::DrawSetFillColor(0, 0, 0, 0);

      ESAT::DrawSetStrokeColor(255, 255, 255, 255);

      ESAT::DrawSolidPath(path_points, 5, true);
    }

    if (buttons_[i]->img_) {
      
      //Adjust background image to button
      float sprite_width = ESAT::SpriteWidth(buttons_[i]->img_);
      float sprite_height = ESAT::SpriteHeight(buttons_[i]->img_);
      ESAT::Mat3 translate, escale, transform;
      ESAT::Mat3InitAsScale((float)width/sprite_width, (float)height/sprite_height, &escale);
      ESAT::Mat3InitAsTranslate(buttons_[i]->pos_.x, buttons_[i]->pos_.y, &translate);
      ESAT::Mat3Multiply(translate, escale, &transform);
      
      ESAT::DrawSpriteWithMatrix(buttons_[i]->img_, transform);
    }

    ESAT::DrawSetTextSize(25);

    if (buttons_[i]->text_.c_str()) {
      ESAT::DrawText(x+margin, y+2*margin, buttons_[i]->text_.c_str());
    }
  }
}


/// @brief  Stablishes initial font settings
void Screen::InitText() {
  ESAT::DrawSetTextFont("assets/font/medieval.ttf");
  ESAT::DrawSetTextSize(40);
  ESAT::DrawSetFillColor(0, 0, 0);
  ESAT::DrawSetStrokeColor(0, 0, 0);
}

/// @brief  Checks and returns the index of the button clicked inside g_option_buttons. Returns -1 if no button is clicked.
int Screen::CheckButtonsClick() {
  int i, click = 0;
  float x = 0.0f;
  float y = 0.0f;
  float height = 0.0f;
  float width = 0.0f;

  for (i = 0; i < buttons_.size() && !click; i++) {
    x = buttons_[i]->pos_.x;
    y = buttons_[i]->pos_.y;
    height = buttons_[i]->height_;
    width = buttons_[i]->width_;

    //Check if clicked inside the button
    if (ESAT::MousePositionX() > x
      && ESAT::MousePositionX() < x + width
      && ESAT::MousePositionY() > y
      && ESAT::MousePositionY() < y + height) {
      click = 1;
    }
  }
  return (click) ? i - 1 : -1;
}

/// @brief  An alias for Screen::CheckButtonsClick(), to be used for detecting hover
int Screen::CheckButtonsHover() {
  return CheckButtonsClick();
}

void Screen::DrawTextWithLineBreaks(float x, float y, int width, int font_size, std::string txt) {
  ESAT::DrawSetTextSize(font_size);
  
  int chars_per_line = width / font_size;
  int num_lines = ceil(txt.length()/(chars_per_line));
  
  for (int i=0; i <= num_lines; i++) {
    ESAT::DrawText(x, y+((i+1)*font_size), txt.substr (i*chars_per_line, chars_per_line).c_str());
  }
}


void Screen::DrawRectangle(float x, float y, int width, int height, int color, bool faces_right) {
    
  if (!faces_right) {
    x -= width;
  }

  float path_points[] = { x, y,
    x + width, y,
    x + width, y + height,
    x, y + height,
    x, y
  };

  int red = (color & 0xFF000000) >> 24;
  int green = (color & 0x00FF0000) >> 16;
  int blue = (color & 0x0000FF00) >> 8;
  int alpha = (color & 0x000000FF);
  
  ESAT::DrawSetFillColor(red, green, blue, alpha);

  ESAT::DrawSetStrokeColor(255, 255, 255, 255);

  ESAT::DrawSolidPath(path_points, 5, true);
}

/// @brief  Prints a TextBox
void Screen::DrawTextBox(TextBox box) {
  int padding = 20;

  float pathPoints[] = { box.pos.x, box.pos.y,
    box.pos.x + box.size*8.0f, box.pos.y,
    box.pos.x + box.size*8.0f, box.pos.y + box.size,
    box.pos.x, box.pos.y + box.size,
    box.pos.x, box.pos.y
  };

  ESAT::DrawSetFillColor(30, 30, 0);

  ESAT::DrawSetStrokeColor(255, 255, 255);

  ESAT::DrawSolidPath(pathPoints, 5, true);

  ESAT::DrawSetFillColor(150, 150, 150);
  ESAT::DrawText(box.pos.x, box.pos.y + padding, box.txt.c_str());
}