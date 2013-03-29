//
//  ttRope.h
//  springBreak02
//
//  Created by PengCheng on 3/28/13.
//
//

#ifndef __springBreak02__ttRope__
#define __springBreak02__ttRope__

#include "ofMain.h"
#include "ofxBox2d.h"
class ttRope{
public:
    void setup(int num);
    void updateAccelerometer(ofPoint acc);
    void update(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB);
    void draw();
    
    ofPoint translate_A, translate_B;
    ofPoint offset_A, offset_B;
    ofxBox2d world;
    ofxBox2dRect start;
    ofxBox2dRect end;
    ofxBox2dJoint joint;
    
    ofPoint endPos;
    float length;
    int ropeNum;
    bool bHooked;
    bool bRopeInUse;
    int counter;

    
};

#endif /* defined(__springBreak02__ttRope__) */
