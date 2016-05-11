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

#include "../../include/Manager.h"
#include "../../include/Physics.h"
#include "../../include/Pieces/Piece.h"
#include "../../include/Button.h"
#include "Screen.h"

class Game: public Screen {
  
  public:

    Game();
    Game(const Game& orig);
    ~Game();

    void restartLevel();
    void Init();
    void Input();
    void Update(double delta);
    void Draw();
    void CreateButtons() override;
    
    void startSimulation();
    void stopSimulation();
    
    bool exit_ = false;

    float menu_width_ = 300.0f;
    
    Physics* physics_;
    std::vector<Piece*> pieces_;
    Piece* ball_;
    Piece* goal_;

  private:
    
};

#endif /* GAME_H */

