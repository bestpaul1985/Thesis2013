//
//  inGameMenu.h
//  final02
//
//  Created by PengCheng on 5/5/13.
//
//

#ifndef __final02__inGameMenu__
#define __final02__inGameMenu__

#include "ofMain.h"

class inGameMenu{
public:
    void setup();
    void update();
    void draw();
    void touchDown(int x, int y, int TouchId);
    void touchMove(int x, int y, int TouchId);
    void touchUp(int x, int y, int TouchId);
    
    ofImage button;
    ofPoint orgPos;
    ofPoint startPos;
    bool goMain;
    bool show;
};

#endif /* defined(__final02__inGameMenu__) */
