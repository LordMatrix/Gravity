/* 
 * File:   Map.cc
 * Author: Marcos Vazquez
 * 
 * Created on November 15, 2015, 12:13 AM
 */

#include "../include/Level.h"
#include "ESAT/draw.h"

Level::Level() {
}

Level::Level(int id, Piece* b, Piece* g, cpSpace* space) {
  //This should be replaced by a Database
  won_ = false;
  float start_x, x, y;
  
  load(id, space);
  
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

void Level::load(int id, cpSpace* space) {
  sqlite3 *db;
  const char *zErrMsg = 0;
  int rc;
  std::string sql;
  MathLib::Point2 init;
  sqlite3_stmt* rs;
  
  
  rc = sqlite3_open("assets/gravity.db", &db);
  
  //Fetch ball&goal
  sql = "SELECT * FROM level WHERE id="+std::to_string(id);
  rc = sqlite3_prepare(db, sql.c_str(), 100, &rs, &zErrMsg);

  
  //CREATE BALL
  while (sqlite3_step(rs) == SQLITE_ROW) {
    
    init = {(float)sqlite3_column_int(rs,2), (float)sqlite3_column_int(rs,3)};
    Piece* ball = new Ball(init, false, BALL_TYPE, space);
    
    ball->points_.clear();
    ball->width_ = 25.0f;
    ball->height_ = 25.0f;
    MathLib::Vec2 position_offset = {0.0f, 0.0f};
    MathLib::assignRegularPolygon(20, 30, position_offset, 0.0f, ball->points_);
    
    
    //Save this piece reference
    ball_ = ball;
    ball->movable_ = false;
    pieces_.push_back(ball);
    
    
    //CREATE GOAL
    init = {(float)sqlite3_column_int(rs,4), (float)sqlite3_column_int(rs,5)};
    Piece* goal = new Piece(init, true, GOAL_TYPE, space);
    goal->movable_ = false;
    
    goal->img_ = ESAT::SpriteFromFile("assets/img/goal.png");
    goal->width_ = 100.0f;
    goal->height_ = 100.0f;
    goal->img_pivot_ = {-50.0f, -50.0f};
    pieces_.push_back(goal);
    //Save this piece reference
    goal_ = goal;
  }
  
  
  //FETCH LEVEL PIECES FROM DB
  sql = "SELECT * FROM level_piece_index WHERE level_id="+std::to_string(id);
  
  rc = sqlite3_prepare(db, sql.c_str(), 100, &rs, &zErrMsg);
  
  if (rc != SQLITE_OK)
    printf("ERROR");
  
  while (sqlite3_step(rs) == SQLITE_ROW) {
    int piece_id = sqlite3_column_int(rs,2);
    int rotation = sqlite3_column_int(rs,3);
    int pivot_x = sqlite3_column_int(rs,4);
    int pivot_y = sqlite3_column_int(rs,5);
    int movable = sqlite3_column_int(rs,6);
    int position_x = sqlite3_column_int(rs,7);
    int position_y = sqlite3_column_int(rs,8);
    
    init = {(float)position_x, (float)position_y};
    
    
    Piece* piece;
    
    switch (piece_id) {
      case 1:
        piece = new SmallRamp(init, true, 0, space);
        break;
      case 2:
        piece = new LargeRamp(init, true, 0, space);
        break;
      case 3:
        piece = new Wall(init, true, 0, space);
        break;
      case 4:
        piece = new Spring(init, true, SPRING_TYPE, space);
        break;
      case 5:
        piece = new Bouncer(init, true, BOUNCER_TYPE, space);
        break;
      case 6:
        if (rotation == 90)
          piece = new ConveyorBelt(init, true, CONVEYORBELT_INVERTED_TYPE, space);
        else
          piece = new ConveyorBelt(init, true, CONVEYORBELT_TYPE, space);
        break;
      case 7:
        piece = new BowlingBall(init, false, 0, space);
        break;
      case 8:
        piece = new Ball(init, false, 0, space);
        break;
      case 9:
        piece = new SeeSaw(init, false, 0, space);
        break;
      case 10:
        piece = new Rope(init, false, 0, space);
        break;
    }
    
    if (rotation)
      piece->rotation_ = rotation;
    
    if (pivot_x || pivot_y)
      piece->img_pivot_ = {(float)pivot_x, (float)pivot_y};
    
    piece->movable_ = (movable==1);
    
    pieces_.push_back(piece);
  }
  
  sqlite3_finalize(rs);
  sqlite3_close(db);
}


std::vector<std::string> Level::LoadLevelNames() {
  
  std::vector<std::string> names;
  sqlite3 *db;
  const char *zErrMsg = 0;
  int rc;
  std::string sql;
  sqlite3_stmt* rs;
  
  rc = sqlite3_open("assets/gravity.db", &db);
  
  sql = "SELECT name FROM level";
  rc = sqlite3_prepare(db, sql.c_str(), 100, &rs, &zErrMsg);

  while (sqlite3_step(rs) == SQLITE_ROW) {
    std::string text((char*)sqlite3_column_text(rs,0));
    names.push_back(text);
  }
  
  return names;
}