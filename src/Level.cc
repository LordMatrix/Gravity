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
      goal_init = {600.0f, 620.0f};
      
      //SCENE PIECES
      init = {0.0f, 0.0f};
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      piece = new LargeRamp(init, true, 0, space);
      pieces_.push_back(piece);
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
      pieces_.push_back(piece);
      
      init = {367.0, 130.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {525.0, 275.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {260.0, 550.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      
      init = {520.0, 650.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      
      init = {730.0, 650.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      break;
     
      
    case 2:
      goal_init = {450.0f, 720.0f};
      init = {0.0f, 0.0f};
      
      piece = new Spring(init, true, SPRING_TYPE, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {525.0, 228.0};
      piece = new Bouncer(init, true, BOUNCER_TYPE, space);
      pieces_.push_back(piece);
      
      init = {525.0, 343.0};
      piece = new Bouncer(init, true, BOUNCER_TYPE, space);
      pieces_.push_back(piece);
      
      init = {305.0, 485.0};
      piece = new Bouncer(init, true, BOUNCER_TYPE, space);
      pieces_.push_back(piece);
      
      init = {305.0, 610.0};
      piece = new Bouncer(init, true, BOUNCER_TYPE, space);
      pieces_.push_back(piece);
      
      init = {100.0, 225.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {307.0, 285.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {510.0, 516.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      break;
      
    case 3:
      goal_init = {895.0f, 595.0f};
      
      init = {0.0f, 0.0f};
      piece = new ConveyorBelt(init, true, CONVEYORBELT_TYPE, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      
      init = {185.0, 400.0};
      piece = new Bouncer(init, true, BOUNCER_TYPE, space);
      pieces_.push_back(piece);
      
      init = {205.0, 240.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {395.0, 107.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {395.0, 305.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      piece = new ConveyorBelt(init, true, CONVEYORBELT_TYPE, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      piece = new ConveyorBelt(init, true, CONVEYORBELT_TYPE, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      
      init = {430.0, 610.0};
      piece = new Bouncer(init, true, BOUNCER_TYPE, space);
      pieces_.push_back(piece);
      
      init = {530.0, 710.0};
      piece = new Bouncer(init, true, BOUNCER_TYPE, space);
      pieces_.push_back(piece);
      
      init = {210.0, 555.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {975.0, 345.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {975.0, 545.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {815.0, 545.0};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {510.0, 225.0};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      
      init = {705.0, 225.0};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      
      init = {895.0, 663.0};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      
      init = {895.0, 225.0};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
     
      init = {734.0, 465.0};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      
      init = {695.0, 663.0};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      
      piece = new SmallRamp(init, true, 0, space);
      piece->rotation_ = -90.0f;
      piece->img_pivot_ = {-50.0f, 50.0f};
      pieces_.push_back(piece);
      break;
    
    case 4:
      goal_init = {780.0f, 680.0f};
      
      piece = new Spring(init, true, SPRING_TYPE, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      piece = new Spring(init, true, SPRING_TYPE, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      piece = new Spring(init, true, SPRING_TYPE, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      piece = new SmallRamp(init, true, 0, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      piece = new ConveyorBelt(init, true, CONVEYORBELT_INVERTED_TYPE, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      
      init = {135.0f, 300.0f};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {370.0f, 300.0f};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {630.0f, 300.0f};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {1035.0f, 200.0f};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {1035.0f, 400.0f};
      piece = new Wall(init, true, 0, space);
      pieces_.push_back(piece);
      
      init = {955.0f, 520.0f};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      
      init = {750.0f, 380.0f};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      
      init = {500.0f, 380.0f};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      
      init = {255.0f, 380.0f};
      piece = new Wall(init, true, 0, space);
      piece->rotation_ = 90.0f;
      piece->img_pivot_ = {100.0f, -20.0f};
      pieces_.push_back(piece);
      break;
      
    case 5:
      goal_init = {780.0f, 680.0f};
      
      piece = new BowlingBall(init, false, 0, space);
      pieces_.push_back(piece);
      piece = new Ball(init, false, 0, space);
      pieces_.push_back(piece);
      
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
      piece = new SmallRamp(init, true, 0, space);
      pieces_.push_back(piece);
//      
      init = {395.0, 600.0};
      piece = new SeeSaw(init, false, 0, space);
      piece->movable_ = true;
      pieces_.push_back(piece);
      break;
      
    default:
      printf("ERROR: Level not coded\n");
      break;
  }
  

  //BALL
  ball = new Ball(goal_init, false, BALL_TYPE, space); 
  //Additional ball properties
  ball->points_.clear();
  ball->width_ = 25.0f;
  ball->height_ = 25.0f;
  position_offset = {0.0f, 0.0f};
  MathLib::assignRegularPolygon(6, 30, position_offset, 0.0f, ball->points_);
  
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
  
  goal->img_ = ESAT::SpriteFromFile("assets/img/goal.png");
  goal->width_ = 100.0f;
  goal->height_ = 100.0f;
  goal->img_pivot_ = {-50.0f, -50.0f};
  pieces_.push_back(goal);
  //Save this piece reference
  goal_ = goal;
  
  
  //Place NON-STATIC pieces in inventory (menu area)
  start_x = kWinWidth - kMenuWidth + 70.0f;
  x = start_x;
  y = 50.0f;
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