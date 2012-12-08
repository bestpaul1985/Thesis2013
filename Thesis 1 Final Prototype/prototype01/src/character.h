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
    void setup(ofxBox2dRect &rect, float _speed, float _scale, float _dump);
    void update(bool L, bool R);
    void draw(ofxBox2dRect &rect);
    
    ofImage *img;
    ofPoint pos;
    ofPoint frc;
    float width;
    float height;
    float density;
    float bounce;
    float friction;
    float offSetX;
    float offSetY;
    float speed;
    float scale;
    float dump;
};

#endif /* defined(__prototype01__character__) */
