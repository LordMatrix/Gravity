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

Level::Level(const Level& orig) {
}


Level::~Level() {
  printf("LEVEL IS BEING DELETED\n");
}


void Level::LoadFromFile(std::string filename, Level* levels[10]) {
}

