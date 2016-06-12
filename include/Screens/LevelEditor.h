/* Copyright 2016 Marcos Vazquez. All rights reserved.    
 * 
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>  
 * Created on June 11, 2016, 10:45 PM
 *
 * File:   LevelEditor.h                                              
 * A class holding a level editor
 *
 */

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H 1

#include <vector>

#include "../../include/Manager.h"
//#include "../../include/Physics.h"
#include "../../include/Pieces/Piece.h"
#include "../../include/Button.h"
#include "Screen.h"
#include "../Level.h"

class Level;

class LevelEditor: public Screen {
  
  public:

    LevelEditor();
    LevelEditor(const LevelEditor& orig);
    ~LevelEditor();

    void restartLevel();
    void Init();
    void Update(double delta);
    void Draw() override;
    void CreateButtons() override;
    void deleteButtons();
    
    bool exit_ = false;
    
    Level* level_;

  private:
    
    Piece* createPiece(MathLib::Point2 initial_pos, bool is_static, int collision_type);
    void createPieces();
    void loadAllPieces();
    
    std::vector<Piece*> templates_;
};

#endif /* LEVELEDITOR_H */

