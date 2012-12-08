//
//  character.h
//  prototype01
//
//  Created by PengCheng on 12/7/12.
//
//

#ifndef __prototype01__character__
#define __prototype01__character__

#include "ofMain.h"
#include "ofxBox2d.h"

class character{
    
public:
    void setup(ofxBox2d world, float x, float y, float width, float height);
    void update(bool L, bool R,float speed, float scale, float dump);
    void draw();
    

    ofxBox2dRect box2d;
    float density;
    float bounce;
    float friction;
    ofImage *img;
    float offSetX;
    float offSetY;
};

#endif /* defined(__prototype01__character__) */
