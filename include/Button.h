/* 
 * File:   Button.h
 * Author: Marcos Vazquez
 *
 * Created on May 8, 2015, 18:24 PM
 */

#ifndef BUTTON_H
#define BUTTON_H 1

#include <math.h>
#include <stdlib.h>
#include <string>
#include "MathLib.h"
#include <ESAT/window.h>
#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h> 

class Button {
public:

  MathLib::Point2 pos_;
  ESAT::SpriteHandle img_;
  std::string text_;
  float height_;
  float width_;
  unsigned short int option_;
  bool border_;
  

  Button();
  Button(float x, float y, float height, float width,
  int option, ESAT::SpriteHandle img, std::string txt, bool has_border);
  Button(const Button& orig);
  virtual ~Button();

  void virtual init();
  void virtual input();
  void virtual update();
  void virtual draw();

  void DrawRectangle(float x, float y, int width, int height, int color, bool faces_right);
  bool checkClick();
  bool checkHover();
  
  ESAT::SpriteHandle background_;
  ESAT::SpriteHandle cursor_sprite_;
  ESAT::SpriteHandle button_background_;
  
  bool click_ = false;
  
  
protected:
  
  void initText();
  
  float path_points_[100];
  int num_points_;
  
};

#endif /* BUTTON_H */

