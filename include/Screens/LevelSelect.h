/* 
 * File:   LevelSelect.h
 * Author: Marcos Vazquez
 *
 * Created on November 15, 2015, 11:55 PM
 */

#ifndef LEVELSELECT_H
#define LEVELSELECT_H 1

#include "Screen.h"
//#include "MainMenu.h"
#include "../Manager.h"

class LevelSelect: public Screen {
public:
    LevelSelect();
    LevelSelect(const LevelSelect& orig);
    virtual ~LevelSelect();
    
    void Update(double delta) override;
    void Draw() override;
    
    void createButtons();
    
private:

};

#endif /* LEVELSELECT_H */

