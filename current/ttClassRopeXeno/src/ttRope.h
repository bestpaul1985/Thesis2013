//
//  ttRope.h
//  thatThey
//
//  Created by PengCheng on 3/12/13.
//
//

#ifndef __thatThey__ttRope__
#define __thatThey__ttRope__

#include "ofMain.h"
#include "ofxBox2d.h"
class ttRope{
public:
    void setup(ofPoint CharPos, int Num_char /* 0 = char_A, 1 = char_B */, ofxBox2d&dummyWorld );
    void update(ofPoint AccFrc,ofPoint CharPos);
    void controlRope();
    void pullRope();
    void draw();
    ofPoint         tempPos;
    ofPoint         charPos;
    ofPoint         accFrc;
    ofPoint         accXeno;
    
    int             num_char;
    
    // stuffs for Xenoing data
    float           dist, catchUpSpeed, strength, damping;
    
    //rope/world interaction objects
    ofxBox2dCircle  ropeEnd;
    
};

#endif /* defined(__thatThey__ttRope__) */
