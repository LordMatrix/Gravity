/* 
 * File:   Button.cc
 * Author: Marcos Vazquez
 *
 * Created on May 8, 2015, 18:24 PM
 */

#include "../include/Button.h"


/// @brief Creates a screen and loads its sprites
Button::Button() {
    init();
}


/** @brief Creates a interactive t_Button and saves it to g_option_buttons
*  @param x X coordinate of the top-left corner
*  @param y Y coordinate of the top-left corner
*  @param height Number of pixels height
*  @param width Number of pixels width
*  @param option If this is an ingame button, this is used as selection of movement (Rock/Paper/scissors)
*  @param img   An image that will be placed inside the button. It'll be ignored if NULL
*  @param txt   A text that will be displayed inside the button. It'll be ignored if NULL
*  @param height Whether a blue border will be drawn or not
*/
Button::Button(float x, float y, float height, float width,
  int option, ESAT::SpriteHandle img, std::string txt, bool has_border) {
  
  pos_ = {x, y};
  this->img_ = img;

  this->text_ = txt;

  this->height_ = height;
  this->width_ = width;
  this->option_ = option;
  this->border_ = has_border;
  
  init();
}


Button::Button(const Button& orig) {
}

Button::~Button() {
}

void Button::init() {
  //Assigns a square as default
  float path_points[] = { pos_.x, pos_.y,
      pos_.x + width_, pos_.y,
      pos_.x + width_, pos_.y + height_,
      pos_.x, pos_.y + height_,
      pos_.x, pos_.y
    };
  
  //copy to class variable
  for (int i=0; i<10; i++) {
    path_points_[i] = path_points[i];
  }
  
  num_points_ = 5;
  
  initText();
}

/// @brief Detects mouse click
void Button::input() {
  click_ = ESAT::MouseButtonUp(0);
}

/** @brief Updates the button
 */
void Button::update() {

}

/// @brief Draws the screen
void Button::draw() {
  float margin = 30.0f;

  ESAT::DrawSetFillColor(100, 0, 0, 255);
  ESAT::DrawSetStrokeColor(100,0,0, 255);
    
  if (border_) {
    ESAT::DrawPath(path_points_, num_points_);
  }

  if (img_) {
    //Adjust background image to button
    float sprite_width = ESAT::SpriteWidth(img_);
    float sprite_height = ESAT::SpriteHeight(img_);
    ESAT::Mat3 translate, scale, transform;
    ESAT::Mat3InitAsScale((float)width_/sprite_width, (float)height_/sprite_height, &scale);
    ESAT::Mat3InitAsTranslate(pos_.x, pos_.y, &translate);
    ESAT::Mat3Multiply(translate, scale, &transform);

    ESAT::DrawSpriteWithMatrix(img_, transform);
  }

  ESAT::DrawSetTextSize(25);

  if (text_.c_str()) {
    ESAT::DrawText(pos_.x+margin, pos_.y+margin, text_.c_str());
  }
}



/// @brief  Stablishes initial font settings
void Button::initText() {
  ESAT::DrawSetTextFont("../assets/font/medieval.ttf");
  ESAT::DrawSetTextSize(40);
  ESAT::DrawSetFillColor(0, 200, 0, 255);
  ESAT::DrawSetStrokeColor(0, 0, 0, 0);
}

/// @brief  Checks and returns if the button has been clicked
bool Button::checkClick() {
  int click = false;

  //Check if clicked inside the button
  if (ESAT::MousePositionX() > pos_.x
    && ESAT::MousePositionX() < pos_.x + width_
    && ESAT::MousePositionY() > pos_.y
    && ESAT::MousePositionY() < pos_.y + height_) {
    click = 1;
  }
    
  return click;
}

/// @brief  An alias for CheckClick(), to be used for detecting hover
bool Button::checkHover() {
  return checkClick();
}



void Button::DrawRectangle(float x, float y, int width, int height, int color, bool faces_right) {
    
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