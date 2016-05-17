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
  
  Piece* ball;
  Piece* goal;
  Piece* piece;
  MathLib::Vec2 position_offset;
  
  switch (id) {
    case 0:
      
      MathLib::Point2 init;
  
  
      //Ball position restarts on simulation play
      init = {0.0f, 0.0f};
      ball = new Piece(init, false, BALL_TYPE, space); 

      //Additional ball properties
      ball->points_.clear();
      position_offset = {0.0f, 0.0f};
      MathLib::assignRegularPolygon(20, 30, position_offset, 0.0f, ball->points_);
      ball->initial_pos_ = {100.0f, 0.0f};
      ball->set_pos_ = ball->initial_pos_;
      ball->current_pos_ = ball->initial_pos_;
      //Save this piece reference
      ball_ = ball;
      pieces_.push_back(ball);


      //GOAL
      init = {100.0f, 600.0f};
      goal = new Piece(init, true, GOAL_TYPE, space);
      pieces_.push_back(goal);
      //Save this piece reference
      goal_ = goal;


      //SCENE PIECES
      init = {900.0f, 500.0f};
      piece = new SmallRamp(init, true, 0, space);
      
      pieces_.push_back(piece);

      init = {900.0f, 200.0f};
      piece = new LargeRamp(init, true, 0, space);
      pieces_.push_back(piece);

      //Place NON-STATIC pieces in inventory (menu area)
      break;
    default:
      printf("ERROR: Level not coded\n");
      break;
  }
}

Level::Level(const Level& orig) {
}


Level::~Level() {
  printf("LEVEL IS BEING DELETED\n");
}