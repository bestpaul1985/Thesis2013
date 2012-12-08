//
//  dirctiveButton.h
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#ifndef __prototype01__dirctiveButton__
#define __prototype01__dirctiveButton__

#include "ofMain.h"
class directiveButton{
    
public:
    void setup(float x, float y, float _num, float _angle);
    void draw();
    void touchDown(int x, int y, int touchId);
    void touchMoved(int x, int y, int touchId);
    void touchUp(int x, int y, int touchId);
    
    ofRectangle         rect;
    ofImage             img;
    ofColor             color;
    bool                bPressed;
    int                 num;
    float               angle;
    
    
};

#endif /* defined(__prototype01__dirctiveButton__) */
