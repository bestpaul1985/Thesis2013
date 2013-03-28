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
#include "ttSetData.h"
class ttRope{
public:
    void setup(ttChar &chraA, ttChar &chraB, int num);
    void setupContactListener();
    void update();
    void cameraUpdate(ofCamera cam_A, ofCamera cam_B);
    void accelerometerUpdate(ofPoint Acc);
    void draw();
    void swing();
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
    
    ofxBox2dRect dummy;
    ofPoint frc, dumScreen, ropeScreen;
    ofxBox2d world;
    ttChar *char_A;
    ttChar *char_B;
    ofxBox2dRect start;
    vector<ofxBox2dRect>    rects;
    vector<b2RevoluteJoint*> joints;
    
    int ropeNum;
    float startTime;
    float duration;
    bool bFixRope;
    int swingNum;
};

#endif /* defined(__springBreak01__ttRope__) */
