/* Copyright 2016 Marcos Vazquez. All rights reserved.
 *
 * Author: Marcos Vazquez <vazquezre@esat-alumni.es>
 *
 * File:   main.cc               
 * An Incredible Machine / Isaac Newton's Gravity ripoff with focus on physics simulation.
 *
 */

//#ifndef WIN32
//#define WIN32 1
//#endif

#include "ESAT/window.h"
#include "ESAT/draw.h"
#include "ESAT/input.h"
 
#include <iostream>
#include "time.h"

#include "../include/Piece.h"
#include "ESAT_extra/chipmunk/chipmunk.h" 
#include "../include/config.h"
#include "../include/Button.h"

ESAT::SpriteHandle g_cursor_sprite_;
float g_menu_width = 300.0f;
bool g_simulation_running;
bool g_simulation_started;

std::vector<Button*> g_buttons;

cpSpace* g_space = nullptr;

ESAT::SpriteHandle g_bg;
std::vector<Piece*> g_pieces;
Piece* g_ball;


struct {
  int width;
  int height;
} WindowOptions = {kWinWidth, kWinHeight};


/************* PHYSICS CONTROL *************/
void deleteBody(cpBody *body, void *data) {
  cpSpaceRemoveBody(cpBodyGetSpace(body), body);
}


void deleteShape(cpShape *shape, void *data) {
  cpSpaceRemoveShape(cpShapeGetSpace(shape), shape);
  cpShapeFree(shape);
}


void deleteAllShapes(cpSpace *space, void *key, void *data) {
  if (!g_simulation_started && !g_simulation_running) {
    printf("deleting shizz\n");
    cpSpaceEachShape(g_space, deleteShape, NULL);
  }
}

void drawBody(cpBody *body, void *data) {

}


void drawShape(cpShape *shape, void *data) {
  ESAT::DrawSetStrokeColor(255,0,0,255);
  cpBB bb = cpShapeGetBB(shape);
  float path[] = {bb.l,bb.t, bb.r,bb.t, bb.r,bb.b, bb.l,bb.b, bb.l,bb.t};
  ESAT::DrawPath(path, 5);
}


/**
 * Prints all objects contained in the global space
 */
void drawPhysics() {
  cpSpaceEachBody(g_space, drawBody, NULL);
  cpSpaceEachShape(g_space, drawShape, NULL);
}
/*******************************************/


/**
 * Initializes variables and sets the game to its initial status
 */
void startGame() {
  srand(time(NULL));
  
  g_simulation_running = false;
  g_simulation_started = false;
  
  g_space = cpSpaceNew();
  cpSpaceSetGravity(g_space, cpv(0, 0.0098f));
  
  Piece* piece = new Piece();
  piece->space_ = g_space;
  piece->initial_pos_ = {900.0f, 500.0f};
  piece->set_pos_ = piece->initial_pos_;
  piece->current_pos_ = piece->initial_pos_;
  piece->static_ = true;
  g_pieces.push_back(piece);
  
  Piece* piece2 = new Piece();
  piece2->space_ = g_space;
  piece2->static_ = false;
  g_pieces.push_back(piece2);
  
  //BALL
  Piece* ball = new Piece();
  ball->space_ = g_space;
  ball->static_ = false;
  
  ball->points_.clear();
  MathLib::Vec2 position_offset = {0.0f, 0.0f};
  MathLib::assignRegularPolygon(20, 30, position_offset, 0.0f, ball->points_);
  ball->initial_pos_ = {100.0f, 0.0f};
  ball->set_pos_ = ball->initial_pos_;
  ball->current_pos_ = ball->initial_pos_;
  
  g_ball = ball;
  g_pieces.push_back(ball);
  
  float x = kWinWidth - g_menu_width;

  //Play button
  g_buttons.push_back(new Button(x + 25.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/play.png"), "", false));
  //Pause Button
  g_buttons.push_back(new Button(x + 125.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/pause.png"), "", false));
  //Stop button
  g_buttons.push_back(new Button(x + 225.0f, kWinHeight - 100.0f, 50.0f, 50.0f, 0, ESAT::SpriteFromFile("assets/img/stop.png"), "", false));
}


void restartLevel() {
  //Delete previous pieces
  for (int i=g_pieces.size()-1; i>=0; i--) {
    delete g_pieces[i];
  }
  g_pieces.clear();
  startGame();
}


void startSimulation() {
  
  g_space = cpSpaceNew();
  cpSpaceSetGravity(g_space, cpv(0, 0.0098f));
  for (int i=0; i<g_pieces.size(); i++) {
    g_pieces[i]->space_ = g_space;
    g_pieces[i]->physics_segments_.clear();
  }
  
  //Update pieces physics
  if (!g_simulation_started) {
    g_ball->current_pos_ = {100.0f, 0.0f};
    
    for (int i=0; i<g_pieces.size(); i++) {
      //Check if the piece is inside the menu
      float menu_x = kWinWidth - g_menu_width;
      //Update active status
      g_pieces[i]->active_ = (g_pieces[i]->current_pos_.x < menu_x);
        
      if (g_pieces[i]->active_)
        g_pieces[i]->setPhysics();
    }
  }
  g_simulation_running = true;
  g_simulation_started = true;
}


void pauseSimulation() {
  g_simulation_running = false;
}


void resumeSimulation() {
  g_simulation_running = true;
}


void stopSimulation() {
  
  for (int i=0; i<g_pieces.size(); i++) {
    g_pieces[i]->current_pos_ = g_pieces[i]->set_pos_;
    g_pieces[i]->setPhysics();
  }
  
  g_simulation_started = false;
  g_simulation_running = false;
}


/**
 * Updates the game status
 * @param delta   Milliseconds elapsed since the last update
 */
void update(double delta) {
  //Listen to button click
  if (ESAT::MouseButtonPressed(0)) {
    for (int i=0; i<g_buttons.size(); i++) {
      if (g_buttons[i]->checkClick()) {
        switch(i) {
          case 0:
            //Play
            if (!g_simulation_started) {
              startSimulation();
            } else {
              resumeSimulation();
            }
            break;
          case 1:
            pauseSimulation();
            break;
          case 2:
            stopSimulation();
            break;
        }
        
      }
    }
  }
  //Listen to spacebar press
  if (ESAT::GetNextPressedKey()) {
    if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Space)) {
      
      //Update pieces physics
      if (!g_simulation_started) {
        startSimulation();
      } else {
        if (g_simulation_running) pauseSimulation();
        else resumeSimulation();
      }
    }
  }
  
  if (g_simulation_running) {
    cpSpaceStep(g_space, delta);

    for (int i=0; i<g_pieces.size(); i++) {
      g_pieces[i]->update();
    }
  } else if (!g_simulation_started) {
    
    for (int i=0; i<g_pieces.size(); i++) {
      
      //Detect drag/drop
      if (ESAT::MouseButtonDown(0)) {
        if (g_pieces[i]->checkClick()) {
          g_pieces[i]->dragged_ = !g_pieces[i]->dragged_;
        }
      }
      
      //Move selected piece along with the mouse
      if (g_pieces[i]->dragged_) {
        g_pieces[i]->drop();
      }
    }
  }
}


/**
 * Draws the game status
 */
void draw() {
  ESAT::DrawBegin();
  ESAT::DrawClear(255,255,255);

//  ESAT::DrawSprite(g_bg, 0, 0);

  /************ MENU ************/
  ESAT::DrawSetFillColor(0,0,200,200);
  ESAT::DrawSetStrokeColor(255,255,255,255);
  
  //Draw menu background
  float x = kWinWidth - g_menu_width;
  float path[] = {x,0.0f, x,kWinHeight, kWinWidth,kWinHeight, kWinWidth,0.0f, x,0.0f};
  ESAT::DrawSolidPath(path, 5);
  
  //Draw Buttons
  for (int i=0; i<g_buttons.size(); i++) {
    g_buttons[i]->draw(); 
  }
  /******************************/

  //Draw Pieces
  for (int i=0; i<g_pieces.size(); i++) {
    g_pieces[i]->draw();
  }
  
  ESAT::DrawSprite(g_cursor_sprite_, (float)ESAT::MousePositionX(), (float)ESAT::MousePositionY());
  
  
  drawPhysics();
  
  ESAT::DrawEnd();
  ESAT::WindowFrame();
}


/**
 * @brief The alpha and the omega 
 */
int ESAT::main(int argc, char **argv) {
  

  ESAT::WindowInit(WindowOptions.width, WindowOptions.height);
  
  g_bg = ESAT::SpriteFromFile("assets/img/sky.jpg");
  g_cursor_sprite_ = ESAT::SpriteFromFile("assets/img/Crosshair_02.png");
  
  startGame();
  
  //Init font
  ESAT::DrawSetTextFont("assets/font/medieval.ttf");
  ESAT::DrawSetTextSize(20);
  
  static double last_time = ESAT::Time();
  
  while(ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {

    /****************SIMULATION****************/
    double tick = ESAT::Time();
    double delta = (tick - last_time) * 0.1f;
    last_time = ESAT::Time();
    
    
            
    update(delta);
    draw();
  }
  ESAT::WindowDestroy();
  return 0;
}