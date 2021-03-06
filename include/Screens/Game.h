/* Copyright 2015 Marcos Vazquez. All rights reserved.    
 * 
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>  
 * Created on November 9, 2015, 8:15 PM
 *
 * File:   Game.h                                              
 * A class that represents an the overwiev game
 *
 */

#ifndef GAME_H
#define GAME_H 1

#include <vector>

#include "../../include/Manager.h"
#include "../../include/Physics.h"
#include "../../include/Pieces/Piece.h"
#include "../../include/Button.h"
#include "Screen.h"
#include "../Level.h"

class Physics;

class Game: public Screen {
  
  public:

    Game();
    Game(const Game& orig);
    ~Game();

    void restartLevel();
    void Init();
    void Update(double delta);
    void Draw() override;
    void CreateButtons() override;
    void deleteButtons();
    void loadLevels();
    void levelUp();
    void startSimulation();
    void stopSimulation();
    
    bool exit_ = false;
    
    Physics* physics_;
    std::vector<Level*> levels_;
    int current_index_;
    Level* current_level_;
    
    Piece* ball_;
    Piece* goal_;

  private:
    
    Piece* createPiece(MathLib::Point2 initial_pos, bool is_static, int collision_type);
    void createPieces();
};

#endif /* GAME_H */

