#include "../../include/Screens/LevelEditor.h"

LevelEditor::LevelEditor() {
  Screen();
  Init();
  
  background_ = ESAT::SpriteFromFile("assets/img/game_bg.png");
  new_insert_ = true;
}

LevelEditor::LevelEditor(const LevelEditor& orig) {
}

LevelEditor::~LevelEditor() {
}


void LevelEditor::restartLevel() {
  //Delete previous pieces
  for (int i=level_->pieces_.size()-1; i>=0; i--) {
    delete level_->pieces_[i];
  }
  level_->pieces_.clear();
  Init();
}


/// @brief Creates buttons and loads stats background
void LevelEditor::Init() {
  loadAllPieces();
  CreateButtons();
}


void LevelEditor::Draw() {
  ESAT::DrawBegin();
  ESAT::DrawClear(255,255,255);

  ESAT::Mat3 transform;
  float ratiox = (float)kWinWidth / (float)ESAT::SpriteWidth(background_);
  float ratioy = (float)kWinHeight / (float)ESAT::SpriteHeight(background_);
  
  ESAT::Mat3InitAsScale(ratiox, ratioy, &transform);
  ESAT::DrawSpriteWithMatrix(background_, transform);
  
  /************ MENU ************/
  ESAT::DrawSetFillColor(0,0,200,200);
  ESAT::DrawSetStrokeColor(255,255,255,255);
  
  //Draw menu background
  float x = kWinWidth - kMenuWidth;
  float path[] = {x,0.0f, x,kWinHeight, kWinWidth,kWinHeight, kWinWidth,0.0f, x,0.0f};
  ESAT::DrawSolidPath(path, 5);
  
  //Draw info text
  ESAT::DrawSetTextSize(17.0f);
  ESAT::DrawSetFillColor(255,255,255,255);
  ESAT::DrawText(x+10, 30.0f, "Drop pieces here to make them selectable");
  
  //Draw piece selection area
  float y = 600.0f;
  float path2[] = {0.0f,y, x,y, x,kWinHeight, 0.0f,kWinHeight, 0.0f,y};
  ESAT::DrawSetFillColor(0,150,0,200);
  ESAT::DrawSolidPath(path2, 5);
  
  //Draw Buttons
  for (int i=0; i<buttons_.size(); i++) {
    buttons_[i]->draw(); 
  }
  /******************************/

  //Draw Pieces
  for (int i=0; i<level_->pieces_.size(); i++) {
    level_->pieces_[i]->draw();
  }
  
  //Draw templates
  for (int i=0; i<templates_.size(); i++) {
    templates_[i]->draw();
  }
  
  //Show level name
  ESAT::DrawSetFillColor(255,255,255,255);
  ESAT::DrawSetStrokeColor(255,255,255,255);
  ESAT::DrawText(kWinWidth-kMenuWidth+20, kWinHeight-20.0f, level_->name_.c_str());
  
  ESAT::DrawSprite(cursor_sprite_, (float)ESAT::MousePositionX(), (float)ESAT::MousePositionY());
  //Print mouse coordinates
  InitText();
  ESAT::DrawSetTextSize(15.0f);
  ESAT::DrawText(10.0f, 20.0f, (std::to_string((int)ESAT::MousePositionX())+", "+std::to_string((int)ESAT::MousePositionY())).c_str());
  
  ESAT::DrawEnd();
  ESAT::WindowFrame();
}


void LevelEditor::Update(double delta) {
  
  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    LevelSelect* ls = new LevelSelect();
    Manager::getInstance()->screen_ = ls;
    return;
  }
  //FOR DEBUGGING. DELETE ON RELEASE.
  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Enter)) {
  }
  
  //Listen to button click
  if (ESAT::MouseButtonPressed(0)) {
    for (int i=0; i<buttons_.size(); i++) {
      if (buttons_[i]->checkClick()) {
        switch(i) {
          case 0:
            SaveLevel();
            break;
        }
        
      }
    }
  }
  
  //Append level name
  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Delete)) {
    level_->name_.pop_back();
  } else {
    char key = ESAT::GetNextPressedKey();
    if (key) {
      level_->name_ += key;
    }
  }
    
  //Check clicking on pieces
  bool found = false;
  for (int i=0; i<templates_.size() && !found; i++) {

    //Detect drag/drop
    if (ESAT::MouseButtonDown(0)) {

      if (templates_[i]->checkClick()) {
        Piece* selected = new Piece(*templates_[i]);
        level_->pieces_.push_back(selected);

        printf("Copy is at %f,%f\n", selected->current_pos_.x, selected->current_pos_.y);
        selected->movable_ = true;
        found = true;
      }
    }
  }
  
  if (true) {
    found = false;
    for (int i=0; i<level_->pieces_.size() && !found; i++) {

      //Detect drag/drop
      if (ESAT::MouseButtonDown(0)) {

        if (level_->pieces_[i]->checkClick()) {
          level_->pieces_[i]->dragged_ = !level_->pieces_[i]->dragged_;
          found = true;
        }
      }

      //Move selected piece along with the mouse
      if (level_->pieces_[i]->dragged_) {
        level_->pieces_[i]->drop();
      }
    }
  }

}


void LevelEditor::CreateButtons() {
  float x = kWinWidth - kMenuWidth;

  //Play button
  buttons_.push_back(new Button(x + 25.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/save.png"), "", false));
  
//  buttons_.push_back(new Button(x + 125.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/pause.png"), "", false));
}


void LevelEditor::deleteButtons() {
  for (int i=0; i<buttons_.size(); i++) {
    delete buttons_[i];
  }
  buttons_.clear();
}


void LevelEditor::loadAllPieces() {
  MathLib::Point2 pos = {50.0f, 650.0f};

  templates_.push_back(new SmallRamp(pos, true, 0, nullptr));
  templates_.push_back(new LargeRamp(pos, true, 0, nullptr));
  templates_.push_back(new Wall(pos, true, 0, nullptr));
  templates_.push_back(new Spring(pos, true, 0, nullptr));
  templates_.push_back(new Bouncer(pos, true, 0, nullptr));
  templates_.push_back(new ConveyorBelt(pos, true, 0, nullptr));
  templates_.push_back(new BowlingBall(pos, false, 0, nullptr));
  templates_.push_back(new SeeSaw(pos, false, 0, nullptr));
//  templates_.push_back(new Rope(pos, false, 0, nullptr));
  
  for (int i=1; i<templates_.size(); i++) {
    templates_[i]->initial_pos_.x += templates_[i-1]->initial_pos_.x + templates_[i-1]->width_ * 2/3;
    templates_[i]->set_pos_ = templates_[i]->initial_pos_;
    templates_[i]->current_pos_ = templates_[i]->initial_pos_;
  }
  
  Ball* b = new Ball(pos, false, 0, nullptr);
  Goal* g = new Goal(pos, true, 0, nullptr);
  
  level_ = new Level(12, b, g, nullptr);
  //Create ball
  level_->pieces_.push_back(b);
  b->current_pos_ = {100.0f, 50.0f};
  b->movable_ = true;
  //Create goal
  level_->pieces_.push_back(g);
  g->current_pos_ = {100.0f, 200.0f};
  g->movable_ = true;
  
  level_->ball_ = b;
  level_->goal_ = g;
}


void LevelEditor::SaveLevel() {
  printf("SAVING LEVEL\n");
  
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char sql[500];
  MathLib::Point2 init;
  sqlite3_stmt* rs;
  
  rc = sqlite3_open("assets/gravity.db", &db);
  
  
  /*******************/
  /*   CREATE LEVEL  */
  /*******************/
  if (new_insert_) {
    snprintf(sql, 500, "INSERT INTO Level (name, ball_x, ball_y, goal_x, goal_y) VALUES('%s', %d, %d, %d, %d);", 
            level_->name_.c_str(), (int)level_->ball_->current_pos_.x, (int)level_->ball_->current_pos_.y, (int)level_->goal_->current_pos_.x, (int)level_->goal_->current_pos_.y);
  } else {
    printf("updating %d\n", level_->id_);
    snprintf(sql, 500, "UPDATE Level SET name='%s', ball_x=%d, ball_y=%d, goal_x=%d, goal_y=%d WHERE id=%d;", 
            level_->name_.c_str(), (int)level_->ball_->current_pos_.x, (int)level_->ball_->current_pos_.y, (int)level_->goal_->current_pos_.x, (int)level_->goal_->current_pos_.y, level_->id_);
  }
  
  rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
  
  if (new_insert_) {
    level_->id_ = sqlite3_last_insert_rowid(db);
    new_insert_ = false;
    Manager::getInstance()->num_levels_++;
  }
  
  printf("%s\n", zErrMsg);
  
  
  /*******************/
  /*   SAVE PIECES   */
  /*******************/
  
  //Delete previous pieces
  snprintf(sql, 500, "DELETE FROM level_piece_index WHERE level_id=%d;", level_->id_);
  rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
  
  
  //Scan present pieces
  float menu_x = kWinWidth - kMenuWidth;
  
  //Skip ball&goal indices
  for (int i=2; i<level_->pieces_.size(); i++) {
  
    Piece* piece = level_->pieces_[i];
    bool movable = piece->current_pos_.x >= menu_x;
    
    snprintf(sql, 500, "INSERT INTO level_piece_index (level_id, piece_id, rotation, pivot_x, pivot_y, movable, position_x, position_y) VALUES (%d, %d, 0, 0, 0, %d, %d, %d);", 
            level_->id_, piece->id_, (int)movable, (int)piece->current_pos_.x, (int)piece->current_pos_.y);
    rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
    printf("%s\n", sql);
    printf("%s\n", zErrMsg);
  }
}