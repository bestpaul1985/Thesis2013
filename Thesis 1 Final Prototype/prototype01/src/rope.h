//
//  rope.h
//  prototype01
//
//  Created by PengCheng on 12/10/12.
//
//

#ifndef __prototype01__rope__
#define __prototype01__rope__

#include "ofMain.h"
class rope{
public:
    void setup(float x, float y, int _num);
    void draw();
    
    ofPoint pos;
    int num;
    ofImage img;
    float width;
    float height;
};
#endif /* defined(__prototype01__rope__) */
