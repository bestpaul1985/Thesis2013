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
    void setup(ofPoint &accFrc,ofPoint &_screenA,ofPoint &_screenB, ofPoint &_CharA, ofPoint &_CharB,ttControl &cont, int num);
    void update();
    void send();
    void initialize(ofPoint pos);
    void destroy();
    void draw();
    
    ofxBox2d world;
    vector<ofxBox2dRect>    rects;
    vector<b2RevoluteJoint*> joints;
    
    ofPoint *acc;
    ofPoint *screenA;
    ofPoint *screenB;
    ofPoint *charA;
    ofPoint *charB;
    ttControl *control;
    
    float length;
    float startTime;
    float duration;
    
    bool bReady;
    bool bRopeInUse;
    bool bInitialize;
    bool bInSky;
    bool bSwing;
    
    int counter;
    int ropeNum;
    int m_num;
    int m_preNum;
    int closetRect;
    
    float rectW;
    float rectH;
    float rectOff;
};

#endif /* defined(__springBreak02__ttRope__) */
