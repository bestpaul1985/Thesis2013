//
//  chests.h
//  prototype01
//
//  Created by PengCheng on 12/9/12.
//
//

#ifndef __prototype01__chests__
#define __prototype01__chests__

#include "ofMain.h"


class chests {
public:
    void setup(int _num);
    void update(ofPoint _pos);
    void draw();
    
    ofImage img1;
    ofImage img2;
    ofPoint pos;
    ofPoint getCenter;
    int num;
    
    float width1;
    float height1;
    
    float width2;
    float height2;
    bool  open;
    bool  bFixed;
    

};

#endif /* defined(__prototype01__chests__) */
