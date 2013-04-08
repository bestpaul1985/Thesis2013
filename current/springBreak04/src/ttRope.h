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
    void setup(ofPoint &accFrc,int num);
    void updateAccelerometer();
    void updatePosition(ofPoint translateA,ofPoint translateB, ofPoint offsetA, ofPoint offsetB);
    void updateRope();
    void initializeRope();
    void controlRope();
    void destroyRope();
    void draw();
    
    ofPoint translate_A, translate_B;
    ofPoint offset_A, offset_B;
    ofxBox2d world;
    ofxBox2dRect start;
    ofxBox2dRect end;
    ofxBox2dJoint joint;
    
    vector<ofxBox2dRect>    rects;
    vector<b2RevoluteJoint*> joints;
    
    ofPoint endPos;
    ofPoint *acc;
    float length;
    float startTime;
    float duration;
    
    bool bHooked;
    bool bRopeInUse;
    int counter;
    int ropeNum;
    int m_num;
    int m_preNum;
    
};

#endif /* defined(__springBreak02__ttRope__) */
