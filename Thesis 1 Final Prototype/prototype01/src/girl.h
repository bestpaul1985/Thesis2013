//
//  girl.h
//  prototype01
//
//  Created by PengCheng on 12/8/12.
//
//

#ifndef __prototype01__girl__
#define __prototype01__girl__

#include "ofMain.h"

class girl{
public:
    void setup(float x, float y);
    void update(float x, float y);
    void draw();
    
    ofImage img;
    ofPoint getCenter;
    float width;
    float height;
};

#endif /* defined(__prototype01__girl__) */
