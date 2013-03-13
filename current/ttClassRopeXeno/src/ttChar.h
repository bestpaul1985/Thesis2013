//
//  ttChar.h
//  thatThey
//
//  Created by PengCheng on 3/11/13.
//
//

#ifndef __thatThey__ttChar__
#define __thatThey__ttChar__

#include "ofMain.h"
#include "ofxBox2d.h"

class ttChar{
public:
    ttChar();
    void setup(ofxBox2d &characterWorld, ofxBox2d&dummyWorld);
    void update();
    void draw();
    
    ofxBox2dRect    character;
    ofxBox2dRect    Dummy;
    ofPoint         setPos;
    ofPoint         getPos;
    float           setWidth;
    float           setHeight;
   
};

#endif /* defined(__thatThey__ttChar__) */
