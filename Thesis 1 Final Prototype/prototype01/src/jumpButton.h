//
//  jumpButton.h
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#ifndef __prototype01__jumpButton__
#define __prototype01__jumpButton__

#include "ofMain.h"

class jumpButton{
    
public:
    void setup(float width, float hight, float x, float y, ofColor color);
    void draw();
    void touchDown(int x, int y, int touchId);
    void touchMoved(int x, int y, int touchId);
    void touchUp(int x, int y, int touchId);
    
    ofRectangle         rect;
    ofColor             color;
    bool                bPressed;
    bool                bJumped;
    
};

#endif /* defined(__prototype01__jumpButton__) */
