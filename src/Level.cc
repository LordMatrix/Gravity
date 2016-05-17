/* 
 * File:   Map.cc
 * Author: Marcos Vazquez
 * 
 * Created on November 15, 2015, 12:13 AM
 */

#include "../include/Level.h"
#include "ESAT/draw.h"


Level::Level(int id, Piece* b, Piece* g, cpSpace* space) {
  //This should be replaced by a Database
  won_ = false;
  
  Piece* ball;
  Piece* goal;
  Piece* piece;
  MathLib::Vec2 position_offset;
  MathLib::Point2 init = {0.0f, 0.0f};
  MathLib::Point2 goal_init;
  float start_x, x, y;
  
  
  
  
  switch (id) {
    case 0:
      //goal_init = {620.0f, 620.0f};
      goal_init = {100.0f, 620.0f};
      
      //SCENE PIECES
      init = {0.0f, 0.0f};
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      piece = new LargeRamp(init, true, 0, space);
      pieces_.push_back(piece);

      
      //Place NON-STATIC pieces in inventory (menu area)
      start_x = kWinWidth - kMenuWidth + 70.0f;
      x = start_x;
      y = 50.0f;
        
      
      
      break;
    case 1:
      goal_init = {350.0f, 700.0f};
      init = {0.0f, 0.0f};
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {150.0, 300.0};
      piece = new Wall(init, true, 0, space);
      piece->movable_ = false;
      pieces_.push_back(piece);
      
      init = {367.0, 130.0};
      piece = new Wall(init, true, 0, space);
      piece->movable_ = false;
      pieces_.push_back(piece);
      
      init = {525.0, 275.0};
      piece = new Wall(init, true, 0, space);
      piece->movable_ = false;
      pieces_.push_back(piece);
      
      init = {260.0, 550.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      piece->movable_ = false;
      piece->rotation_ = 90.0f;
      
      init = {520.0, 650.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      piece->movable_ = false;
      piece->rotation_ = 90.0f;
      
      init = {730.0, 650.0};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->movable_ = false;
      pieces_.push_back(piece);
      break;
    default:
      printf("ERROR: Level not coded\n");
      break;
  }
  

  //BALL
  ball = new Piece(goal_init, false, BALL_TYPE, space); 
  //Additional ball properties
  ball->points_.clear();
  position_offset = {0.0f, 0.0f};
  MathLib::assignRegularPolygon(20, 30, position_offset, 0.0f, ball->points_);
  
  ball->initial_pos_ = {100.0f, 0.0f};
  ball->set_pos_ = ball->initial_pos_;
  ball->current_pos_ = ball->initial_pos_;
  
  //Save this piece reference
  ball_ = ball;
  ball->movable_ = false;
  pieces_.push_back(ball);
  
  //GOAL
  goal = new Piece(goal_init, true, GOAL_TYPE, space);
  goal->movable_ = false;
  pieces_.push_back(goal);
  //Save this piece reference
  goal_ = goal;
  
  
  //Place movable pieces on menu space
  for (int i=0; i<pieces_.size(); i++) {
    if (pieces_[i]->movable_) {
      pieces_[i]->initial_pos_ = {x,y};
      pieces_[i]->set_pos_ = pieces_[i]->initial_pos_;
      pieces_[i]->current_pos_ = pieces_[i]->initial_pos_;

      if (i%2==0 && pieces_[i]->colspan_ == 1) {
        x += 150.0f;
      } else {
        x = start_x;
        y += 100.0f;
      }
    }
  }
  
}

Level::Level(const Level& orig) {
}


Level::~Level() {
  printf("LEVEL IS BEING DELETED\n");
}