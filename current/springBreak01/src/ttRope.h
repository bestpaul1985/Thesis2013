//
//  ttRope.h
//  springBreak01
//
//  Created by PengCheng on 3/26/13.
//
//

#ifndef __springBreak01__ttRope__
#define __springBreak01__ttRope__

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ttChar.h"
class ttRope{
public:
    void setup(ttChar &chraA, ttChar &chraB, int num);
    void accelerometerUpdate(ofPoint Acc);
    void update();
    void draw();
    
    ofxBox2dRect dummy, ropeEnd;
    ofPoint frc;
    ofxBox2d world;
    ttChar *char_A;
    ttChar *char_B;
    int ropeNum;
};

#endif /* defined(__springBreak01__ttRope__) */
