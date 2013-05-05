//
//  openingScene.h
//  sceneManager
//
//  Created by Firm Read on 4/10/13.
//
//

#ifndef __sceneManager__openingScene__
#define __sceneManager__openingScene__

#include <iostream>

#include "ofMain.h"
#include "baseScene.h"

class openingScene : public baseScene {
public:
    void setup();
    void update();
    void draw();
    void drawLogo(int x, int y, float scale);

};

#endif /* defined(__sceneManager__openingScene__) */
