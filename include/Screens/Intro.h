/* 
 * File:   Intro.h
 * Author: Marcos Vazquez
 *
 * Created on November 15, 2015, 11:55 PM
 */

#ifndef INTRO_H
#define INTRO_H 1

#include "Screen.h"
//#include "MainMenu.h"
#include "../Manager.h"

class Intro: public Screen {
public:
    Intro();
    Intro(const Intro& orig);
    virtual ~Intro();
    
    void Update();
    void Draw();
    
    unsigned char frame_;
    
private:

};

#endif /* INTRO_H */

