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
    void setup(ofPoint &accFrc,ofPoint &_screenA,ofPoint &_screenB, ofPoint &_CharA, ofPoint &_CharB,ttControl &controlA,ttControl &controlB, int num);
    void update();
    void detect();
    void initialize(ofPoint pos);
    void control();
    void destroy();
    void draw();
    void touchDown(int x, int y, int TouchId);
    void touchMove(int x, int y, int TouchId);
    void touchUp(int x, int y, int TouchId);
    
    
    ofImage img_CharA;
    ofImage img_CharB;
    
    ofxBox2d world;
    ofxBox2dRect start;
    ofxBox2dRect end;
    ofxBox2dJoint joint;
    
    vector<ofxBox2dRect>    rects;
    vector<b2RevoluteJoint*> joints;
    
    ttControl *contA;
    ttControl *contB;
    
    ofPoint *acc;
    ofPoint *screenA;
    ofPoint *screenB;
    ofPoint *charA;
    ofPoint *charB;
    
    float length;
    float startTime;
    float duration;
    
    bool bRopeInHook;
    bool bRopeInUse;
    bool bRopeIsReady;
    int counter;
    int ropeNum;
    int m_num;
    int m_preNum;
    int closestRectNum;
    
};

#endif /* defined(__springBreak02__ttRope__) */
