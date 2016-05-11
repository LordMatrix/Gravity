/* 
 * File:   Screen.h
 * Author: Marcos Vazquez
 *
 * Created on November 15, 2015, 11:55 PM
 */

#ifndef SCREEN_H
#define SCREEN_H 1

#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ESAT/window.h>
#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h> 

#include "../Button.h"
#include "../MathLib.h"

class Screen {
public:

  typedef struct {
    MathLib::Point2 pos;
    int size;
    std::string txt;
  } TextBox;
  
  Screen();
  Screen(const Screen& orig);
  virtual ~Screen();

  void virtual Init();
  void virtual Input();
  void virtual Update(double delta);
  void virtual Draw();
  void DrawCursor();
  void virtual CreateButtons();
  void virtual DrawButtons();
  void DrawTextWithLineBreaks(float x, float y, int width, int font_size, std::string txt);
  void DrawRectangle(float x, float y, int width, int height, int color, bool faces_right);
  void DrawTextBox(TextBox box);
  
  ESAT::SpriteHandle background_;
  ESAT::SpriteHandle cursor_sprite_;
  ESAT::SpriteHandle button_background_;
  
  bool click_ = false;
    
protected:
  void DrawBegin();
  void DrawEnd();
  void InitText();
  int CheckButtonsClick();
  int CheckButtonsHover();
  
  std::vector<Button*> buttons_;

};

#endif /* SCREEN_H */

