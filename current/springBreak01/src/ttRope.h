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
    void setup(ofxBox2d &world,ttChar &chra_A,ttChar &chra_B, ofPoint &accFrc,int num);
    void draw(ofCamera cam_A,ofCamera cam_B);
    
    ttChar *char_A;
    ttChar *char_B;
    ofxBox2dRect rope;
    ofPoint *frc;
    int charNum;
};

#endif /* defined(__springBreak01__ttRope__) */
