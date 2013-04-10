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
class ttRope{
public:
    void setup(ofPoint &accFrc,ofPoint &_screenA,ofPoint &_screenB, ofPoint &_CharA, ofPoint &_CharB,ttControl &cont_A, ttControl &cont_B, int num);
    void update();
    void initialize(ofPoint pos);
    void control();
    void destroy();
    void draw();
    
    ofxBox2d world;
    ofxBox2dRect start;
    ofxBox2dRect end;
    ofxBox2dJoint joint;
    
 
    
    vector<ofxBox2dRect>    rects;
    vector<b2RevoluteJoint*> joints;
    
    ofPoint *acc;
    ofPoint *screenA;
    ofPoint *screenB;
    ofPoint *charA;
    ofPoint *charB;
    ttControl *contA;
    ttControl *contB;
    
    float length;
    float startTime;
    float duration;
    
    bool bHooked;
    bool bReady;
    bool bRopeInUse;
    bool bInitialize;
    bool bFall;
    int counter;
    int ropeNum;
    int m_num;
    int m_preNum;
    int closetRect;
    
};

#endif /* defined(__springBreak02__ttRope__) */
