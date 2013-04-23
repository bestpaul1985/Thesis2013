//
//  ttBird.h
//  afterSpring03
//
//  Created by PengCheng on 4/16/13.
//
//

#ifndef __afterSpring03__ttBird__
#define __afterSpring03__ttBird__

#include "ofMain.h"
#include "ofxBox2d.h"

class ttBird{
public:
    void setup(ofxBox2d &World,float x,float y);
    void update();
    void fly();
//    void takeOff();
//    void landing();
    void draw();
    
    ofxBox2d *world;
    ofxBox2dCircle bird;
    float frcX;
    int cunt;
};

#endif /* defined(__afterSpring03__ttBird__) */
