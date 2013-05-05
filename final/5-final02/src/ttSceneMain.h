//
//  ttSceneMain.h
//  final02
//
//  Created by PengCheng on 5/4/13.
//
//

#ifndef __final02__ttSceneMain__
#define __final02__ttSceneMain__


#include "ofMain.h"
#include "baseScene.h"

class ttSceneMain : public baseScene {
public:
    void setup();
    void update();
    void draw();
    void drawLogo(int x, int y, float scale);
    
};

#endif /* defined(__final02__ttSceneMain__) */
