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
#include "ttControl.h"
#include "ttChar.h"
class ttRope{
public:
    void setup(int num,ttChar &charA,ttChar &charB, ttControl &cont_A, ttControl &cont_B);
    void updateAccelerometer(ofPoint acc);
    void update(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB);
    void draw();
    
    ofPoint translate_A, translate_B;
    ofPoint offset_A, offset_B;
    ofxBox2d world;
    ofxBox2dRect start;
    ofxBox2dRect end;
    ofxBox2dJoint joint;
    ttControl *contr_A, *contr_B;
    ttChar *char_A, *char_B;
    ofPoint endPos;
    float length;
    int  ropeNum;
    bool bHooked;
    bool bRopeInUse;
    int  counter;
    
};

#endif /* defined(__springBreak02__ttRope__) */
