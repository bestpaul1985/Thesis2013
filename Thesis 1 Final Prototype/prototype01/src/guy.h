//
//  guy.h
//  prototype01
//
//  Created by PengCheng on 12/8/12.
//
//

#ifndef __prototype01__guy__
#define __prototype01__guy__

#include "ofMain.h"
class guy{
public:
    void setup(ofPoint _pos);
    void update(ofPoint _pos);
    void draw();
    
    ofImage img;
    ofPoint pos;
    ofPoint getCenter;
    float width;
    float height;
};

#endif /* defined(__prototype01__guy__) */
