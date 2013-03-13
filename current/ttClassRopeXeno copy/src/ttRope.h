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
#include "ttChar.h"
class ttRope{
public:
    void setup(ofPoint _charPos, int _num_char /* 0 = char_A, 1 = char_B */, ofxBox2d &dummyWorld );
    void update(ofPoint _accIn,ofPoint _charPos);
    void controlRopeA(), controlRopeB();
    void ropeBody(ofxBox2d &dummyWorld);
    void draw();
    ofPoint         charPos;
    ofPoint         accIn;
    ofPoint         accXeno;
    ofPoint         pos_A, pos_B;
    
    int             num_char;
    
    // stuffs for Xenoing data
    float           dist, catchUpSpeed, strength, damping;
    
    // rope/dummyWorld interaction objects
    ofxBox2dCircle  ropeEnd;
    
    // rope chain animation
    vector <ofxBox2dRect>   ropeChain;
    vector <ofxBox2dJoint>  joints;
    int             jointLength, ropeChainSize;
    
    bool            ropeCalled;
    
    
};

#endif /* defined(__thatThey__ttRope__) */
